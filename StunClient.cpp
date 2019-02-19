//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <assert.h>
#include "StunClient.h"
#include "SipClient_Unit.h"
#ifndef NOSSL
#include <openssl/hmac.h>
#endif
#define MAX_NIC 3

#pragma package(smart_init)
//---------------------------------------------------------------------------
NatType  TStun::stunNatType( StunAddress4& dest,
             bool* preservePort, // if set, is return for if NAT preservers ports or not
             bool* hairpin,  // if set, is the return for if NAT will hairpin packets
             int port, // port to use for the test, 0 to choose random port
             StunAddress4* sAddr, // NIC to use
             TSip* sip,
             TEventLogThread* elt
   )
{
   assert( dest.addr != 0 );
   assert( dest.port != 0 );

   if ( hairpin )
   {
      *hairpin = false;
   }

   if ( port == 0 )
   {
      port = stunRandomPort();
   }
   UInt32 interfaceIp=0;
   if (sAddr)
   {
      interfaceIp = sAddr->addr;
   }
   Socket myFd1 = openPort(port,interfaceIp,elt);
   Socket myFd2 = openPort(port+1,interfaceIp,elt);

   if ( ( myFd1 == INVALID_SOCKET) || ( myFd2 == INVALID_SOCKET) )
   {
       log(elt,"\nSome problem opening port/interface to send on");
       return StunTypeFailure;
   }

   assert( myFd1 != INVALID_SOCKET );
   assert( myFd2 != INVALID_SOCKET );

   bool respTestI=false;
   bool isNat=true;
   StunAddress4 testIchangedAddr;
   StunAddress4 testImappedAddr;
   bool respTestI2=false;
   bool mappedIpSame = true;
   StunAddress4 testI2mappedAddr;
   StunAddress4 testI2dest=dest;
   bool respTestII=false;
   bool respTestIII=false;

   bool respTestHairpin=false;
   bool respTestPreservePort=false;

   memset(&testImappedAddr,0,sizeof(testImappedAddr));

   StunAtrString username;
   StunAtrString password;

   username.sizeValue = 0;
   password.sizeValue = 0;

#ifdef USE_TLS
   stunGetUserNameAndPassword( dest, username, password );
#endif

   int count=0;
   while ( count < 7 )
   {
      struct timeval tv;
      fd_set fdSet;
#ifdef WIN32
      unsigned int fdSetSize;
#else
      int fdSetSize;
#endif
      FD_ZERO(&fdSet); fdSetSize=0;
      FD_SET(myFd1,&fdSet); fdSetSize = (myFd1+1>fdSetSize) ? myFd1+1 : fdSetSize;
      FD_SET(myFd2,&fdSet); fdSetSize = (myFd2+1>fdSetSize) ? myFd2+1 : fdSetSize;
      tv.tv_sec=0;
      tv.tv_usec=150*1000; // 150 ms
      if ( count == 0 ) tv.tv_usec=0;

      int  err = select(fdSetSize, &fdSet, NULL, NULL, &tv);
      int e = getErrno();
      if ( err == SOCKET_ERROR )
      {
         // error occured
         log(elt,"\nError " + inttostr(e) + " " + strerror(e) + " in select");
        return StunTypeFailure;
     }
      else if ( err == 0 )
      {
         // timeout occured
         count++;

         if ( !respTestI )
         {
            stunSendTest( myFd1, dest, username, password, 1 ,elt );
         }         
			
         if ( (!respTestI2) && respTestI ) 
         {
            // check the address to send to if valid 
            if (  ( testI2dest.addr != 0 ) &&
                  ( testI2dest.port != 0 ) )
            {
               stunSendTest( myFd1, testI2dest, username, password, 10  ,elt);
            }
         }
			
         if ( !respTestII )
         {
            stunSendTest( myFd2, dest, username, password, 2 ,elt );
         }
			
         if ( !respTestIII )
         {
            stunSendTest( myFd2, dest, username, password, 3 ,elt );
         }
			
         if ( respTestI && (!respTestHairpin) )
         {
            if (  ( testImappedAddr.addr != 0 ) &&
                  ( testImappedAddr.port != 0 ) )
            {
               stunSendTest( myFd1, testImappedAddr, username, password, 11 ,elt);
            }
         }
      }
      else
      {
         //if (verbose) clog << "-----------------------------------------" << endl;
         assert( err>0 );
         // data is avialbe on some fd 
			
         for ( int i=0; i<2; i++)
         {
            Socket myFd;
            if ( i==0 ) 
            {
               myFd=myFd1;
            }
            else
            {
               myFd=myFd2;
            }
				
            if ( myFd!=INVALID_SOCKET ) 
            {					
               if ( FD_ISSET(myFd,&fdSet) )
               {
                  char msg[STUN_MAX_MESSAGE_SIZE];
                  int msgLen = sizeof(msg);
                  						
                  StunAddress4 from;
						
                  getMessage( myFd,
                              msg,
                              &msgLen,
                              &from.addr,
                              &from.port,elt);

                  StunMessage resp;
                  memset(&resp, 0, sizeof(StunMessage));

                  stunParseMessage( msg,msgLen,resp,sip,elt );
		  log(elt,"\nReceived message of type " + inttostr(resp.msgHdr.msgType) + "  id=" +
                  inttostr(resp.msgHdr.id.octet[0]));

                  switch( resp.msgHdr.id.octet[0] )
                  {
                     case 1:
                     {
                        if ( !respTestI )
                        {
									
                           testIchangedAddr.addr = resp.changedAddress.ipv4.addr;
                           testIchangedAddr.port = resp.changedAddress.ipv4.port;
                           testImappedAddr.addr = resp.mappedAddress.ipv4.addr;
                           testImappedAddr.port = resp.mappedAddress.ipv4.port;
			
                           respTestPreservePort = ( testImappedAddr.port == port ); 
                           if ( preservePort )
                           {
                              *preservePort = respTestPreservePort;
                           }								
									
                           testI2dest.addr = resp.changedAddress.ipv4.addr;
									
                           if (sAddr)
                           {
                              sAddr->port = testImappedAddr.port;
                              sAddr->addr = testImappedAddr.addr;
                           }
									
                           count = 0;
                        }		
                        respTestI=true;
                     }
                     break;
                     case 2:
                     {  
                        respTestII=true;
                     }
                     break;
                     case 3:
                     {
                        respTestIII=true;
                     }
                     break;
                     case 10:
                     {
                        if ( !respTestI2 )
                        {
                           testI2mappedAddr.addr = resp.mappedAddress.ipv4.addr;
                           testI2mappedAddr.port = resp.mappedAddress.ipv4.port;
								
                           mappedIpSame = false;
                           if ( (testI2mappedAddr.addr  == testImappedAddr.addr ) &&
                                (testI2mappedAddr.port == testImappedAddr.port ))
                           { 
                              mappedIpSame = true;
                           }
								
							
                        }
                        respTestI2=true;
                     }
                     break;
                     case 11:
                     {
							
                        if ( hairpin ) 
                        {
                           *hairpin = true;
                        }
                        respTestHairpin = true;
                     }
                     break;
                  }
               }
            }
         }
      }
   }
	
   // see if we can bind to this address 
   Socket s = openPort( 0/*use ephemeral*/, testImappedAddr.addr, elt );
   if ( s != INVALID_SOCKET )
   {
      closesocket(s);
      isNat = false;
   }
   else
   {
      isNat = true;
   }
      if(respTestI)
        log(elt,"\ntest I = " + (string)"true");
      else
        log(elt,"\ntest I = " + (string)"false");

      if(respTestII)
        log(elt,"\ntest II = " + (string)"true");
      else
        log(elt,"\ntest II = " + (string)"false");

      if(respTestIII)
        log(elt,"\ntest III = " + (string)"true");
      else
        log(elt,"\ntest III = " + (string)"false");

      if(respTestI2)
        log(elt,"\ntest I(2) = " + (string)"true");
      else
        log(elt,"\ntest I(2) = " + (string)"false");

      if(isNat)
         log(elt,"\nis nat = " + (string)"true");
      else
         log(elt,"\nis nat = " + (string)"false");

      if(mappedIpSame)
         log(elt,"\nmapped IP same = " + (string)"true");
      else
         log(elt,"\nmapped IP same = " + (string)"false");

      if(respTestHairpin)
         log(elt,"\nhairpin = " + (string)"true");
      else
         log(elt,"\nhairpin = " + (string)"false");

      if(respTestPreservePort)
         log(elt,"\npreserves port = " + (string)"true");
      else
         log(elt,"\npreserves port = " + (string)"false");

#if 0
   // implement logic flow chart from draft RFC
   if ( respTestI )
   {
      if ( isNat )
      {
         if (respTestII)
         {
            return StunTypeConeNat;
         }
         else
         {
            if ( mappedIpSame )
            {
               if ( respTestIII )
               {
                  return StunTypeRestrictedNat;
               }
               else
               {
                  return StunTypePortRestrictedNat;
               }
            }
            else
            {
               return StunTypeSymNat;
            }
         }
      }
      else
      {
         if (respTestII)
         {
            return StunTypeOpen;
         }
         else
         {
            return StunTypeSymFirewall;
         }
      }
   }
   else
   {
      return StunTypeBlocked;
   }
#else
   if ( respTestI ) // not blocked 
   {
      if ( isNat )
      {
         if ( mappedIpSame )
         {
            if (respTestII)
            {
               return StunTypeIndependentFilter;
            }
            else
            {
               if ( respTestIII )
               {
                  return StunTypeDependentFilter;
               }
               else
               {
                  return StunTypePortDependedFilter;
               }
            }
         }
         else // mappedIp is not same 
         {
            return StunTypeDependentMapping;
         }
      }
      else  // isNat is false
      {
         if (respTestII)
         {
            return StunTypeOpen;
         }
         else
         {
            return StunTypeFirewall;
         }
      }
   }
   else
   {
      return StunTypeBlocked;
   }
#endif

  // return StunTypeUnknown;
}
//-----------------------------------------------------------------------------
bool TStun::stunParseMessage( char* buf, unsigned int bufLen, StunMessage& msg,TSip* sip,TEventLogThread* elt)
{
   log(elt,"\nReceived stun message: " + inttostr(bufLen) + " bytes");
   memset(&msg, 0, sizeof(msg));

   if (sizeof(StunMsgHdr) > bufLen)
   {
      log(elt,"\nBad message");
      return false;
   }

   memcpy(&msg.msgHdr, buf, sizeof(StunMsgHdr));
   msg.msgHdr.msgType = ntohs(msg.msgHdr.msgType);
   msg.msgHdr.msgLength = ntohs(msg.msgHdr.msgLength);

   if (msg.msgHdr.msgLength + sizeof(StunMsgHdr) != bufLen)
   {
      log(elt,"\nMessage header length doesn't match message size: " + inttostr(msg.msgHdr.msgLength) + " - " + inttostr(bufLen));
      return false;
   }

   char* body = buf + sizeof(StunMsgHdr);
   unsigned int size = msg.msgHdr.msgLength;

   //clog << "bytes after header = " << size << endl;

   while ( size > 0 )
   {
      // !jf! should check that there are enough bytes left in the buffer

      StunAtrHdr* attr = reinterpret_cast<StunAtrHdr*>(body);

      unsigned int attrLen = ntohs(attr->length);
      int atrType = ntohs(attr->type);

      //if (verbose) clog << "Found attribute type=" << AttrNames[atrType] << " length=" << attrLen << endl;
      if ( attrLen+4 > size )
      {
         log(elt,"\nclaims attribute is larger than size of message (attribute type=" + inttostr(atrType) + ")");
         return false;
      }

      body += 4; // skip the length and type in attribute header
      size -= 4;

      switch ( atrType )
      {
         case MappedAddress:
            msg.hasMappedAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.mappedAddress,elt )== false )
            {
               log(elt,"\nproblem parsing MappedAddress");
               return false;
            }
            else
              {
              sip->MappedAddress.IPAddr = littleendian_to_dot_str(msg.mappedAddress.ipv4.addr);
              log(elt,"\nMappedAddress = " + sip->MappedAddress.IPAddr);
              }
            break;

         case ResponseAddress:
            msg.hasResponseAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.responseAddress,elt )== false )
            {
               log(elt,"\nproblem parsing ResponseAddress");
               return false;
            }
            else
              log(elt,"\nResponseAddress = " + littleendian_to_dot_str(msg.responseAddress.ipv4.addr));
            break;

         case ChangeRequest:
            msg.hasChangeRequest = true;
            if (stunParseAtrChangeRequest( body, attrLen, msg.changeRequest,elt) == false)
            {
               log(elt,"\nproblem parsing ChangeRequest");
               return false;
            }
            else
               log(elt,"\nChangeRequest = " + inttostr(msg.changeRequest.value));
            break;

         case SourceAddress:
            msg.hasSourceAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.sourceAddress,elt )== false )
            {
               log(elt,"\nproblem parsing SourceAddress");
               return false;
            }
            else
              log(elt,"\nSourceAddress = " + littleendian_to_dot_str(msg.sourceAddress.ipv4.addr));
            break;

         case ChangedAddress:
            msg.hasChangedAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.changedAddress,elt )== false )
            {
               log(elt,"\nproblem parsing ChangedAddress");
               return false;
            }
            else
              log(elt,"\nChangedAddress = " + littleendian_to_dot_str(msg.changedAddress.ipv4.addr));
            break;

         case Username:
            msg.hasUsername = true;
            if (stunParseAtrString( body, attrLen, msg.username,elt) == false)
            {
               log(elt,"\nproblem parsing Username" );
               return false;
            }
            else
               log(elt,"\nUsername = " + string(msg.username.value));
            break;

         case Password:
            msg.hasPassword = true;
            if (stunParseAtrString( body, attrLen, msg.password,elt) == false)
            {
               log(elt,"\nproblem parsing Password");
               return false;
            }
            else
               log(elt,"\nPassword = " + string(msg.password.value));
            break;

         case MessageIntegrity:
            msg.hasMessageIntegrity = true;
            if (stunParseAtrIntegrity( body, attrLen, msg.messageIntegrity,elt) == false)
            {
               log(elt,"\nproblem parsing MessageIntegrity");
               return false;
            }
            else
            {
               //if (verbose) clog << "MessageIntegrity = " << msg.messageIntegrity.hash << endl;
            }

            // read the current HMAC
            // look up the password given the user of given the transaction id
            // compute the HMAC on the buffer
            // decide if they match or not
            break;

         case ErrorCode:
            msg.hasErrorCode = true;
            if (stunParseAtrError(body, attrLen, msg.errorCode,elt) == false)
            {
              log(elt,"\nproblem parsing ErrorCode");
               return false;
            }
            else
            {
               log(elt,"\nErrorCode = " + inttostr(msg.errorCode.errorClass) +
                                   " " + inttostr(msg.errorCode.number)      +
                                   " " + string(msg.errorCode.reason));
            }

            break;

         case UnknownAttribute:
            msg.hasUnknownAttributes = true;
            if (stunParseAtrUnknown(body, attrLen, msg.unknownAttributes,elt) == false)
            {
               log(elt,"\nproblem parsing UnknownAttribute");
               return false;
            }
            break;

         case ReflectedFrom:
            msg.hasReflectedFrom = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.reflectedFrom,elt ) == false )
            {
               log(elt,"\nproblem parsing ReflectedFrom");
               return false;
            }
            break;

         case XorMappedAddress:
            msg.hasXorMappedAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.xorMappedAddress,elt ) == false )
            {
               log(elt,"\nproblem parsing XorMappedAddress");
               return false;
            }
            else
               log(elt,"\nXorMappedAddress = " + littleendian_to_dot_str(msg.xorMappedAddress.ipv4.addr));
            break;

         case XorOnly:
            msg.xorOnly = true;
            log(elt,"\nxorOnly = true");
            break;

         case ServerName:
            msg.hasServerName = true;
            if (stunParseAtrString( body, attrLen, msg.serverName,elt) == false)
            {
               log(elt,"\nproblem parsing ServerName");
               return false;
            }
            else
              log(elt,"\nServerName = " + string(msg.serverName.value));
            break;

         case SecondaryAddress:
            msg.hasSecondaryAddress = true;
            if ( stunParseAtrAddress(  body,  attrLen,  msg.secondaryAddress,elt ) == false )
            {
               log(elt,"\nproblem parsing secondaryAddress");
               return false;
            }
            else
               log(elt,"\nSecondaryAddress = " + littleendian_to_dot_str(msg.secondaryAddress.ipv4.addr));
            break;

         default:
            log(elt,"\nUnknown attribute: " + inttostr(atrType));
            if ( atrType <= 0x7FFF )
            {
               return false;
            }
      }

      body += attrLen;
      size -= attrLen;
   }

   return true;
}
//---------------------------------------------------------------------------
bool TStun::getMessage( Socket fd, char* buf, int* len,
            unsigned int* srcIp, unsigned short* srcPort,
            TEventLogThread* elt)
{
   assert( fd != INVALID_SOCKET );

   int originalSize = *len;
   assert( originalSize > 0 );

   struct sockaddr_in from;
   int fromLen = sizeof(from);

   *len = recvfrom(fd,
                   buf,
                   originalSize,
                   0,
                   (struct sockaddr *)&from,
                   (socklen_t*)&fromLen);

   if ( *len == SOCKET_ERROR )
   {
      int err = getErrno();

      switch (err)
      {
         case ENOTSOCK:
            log(elt,"\nError: fd not a socket");
            break;
         case ECONNRESET:
            log(elt,"\nError: connection reset - host not reachable");
            break;
         default:
            log(elt,"\nSocket Error = " + inttostr(err));
      }

      return false;
   }

   if ( *len < 0 )
   {
      log(elt,"\nsocket closed negative len");
      return false;
   }

   if ( *len == 0 )
   {
      log(elt,"\nsocket closed? zero len");
      return false;
   }

   *srcPort = ntohs(from.sin_port);
   *srcIp = ntohl(from.sin_addr.s_addr);

   if ( (*len)+1 >= originalSize )
   {
   log(elt,"\nReceived a message that was too large");
   return false;
   }
   buf[*len]=0;

   return true;
}
//---------------------------------------------------------------------------
void __fastcall TStun::stunSendTest( Socket myFd, StunAddress4& dest,
              const StunAtrString& username, const StunAtrString& password,
              int testNum, TEventLogThread* elt )
{
   assert( dest.addr != 0 );
   assert( dest.port != 0 );

   bool changePort=false;
   bool changeIP=false;
  // bool discard=false;

   switch (testNum)
   {
      case 1:
      case 10:
      case 11:
         break;
      case 2:
         //changePort=true;
         changeIP=true;
         break;
      case 3:
         changePort=true;
         break;
      case 4:
         changeIP=true;
         break;
      case 5:
       //  discard=true;
         break;
      default:
          log(elt,"\Test " + inttostr(testNum)+ " is unkown");
         assert(0);
   }

   StunMessage req;
   memset(&req, 0, sizeof(StunMessage));

   stunBuildReqSimple( &req, username,
                       changePort , changeIP ,
                       testNum );

   char buf[STUN_MAX_MESSAGE_SIZE];
   int len = STUN_MAX_MESSAGE_SIZE;

   len = stunEncodeMessage( req, buf, len, password,elt );

   log(elt,"\nAbout to send msg of len " + inttostr(len) + (string)" to " + littleendian_to_dot_str(dest.addr) + ":" + inttostr(dest.port));

   sendMessage( myFd, buf, len, dest.addr, dest.port, elt );

   // add some delay so the packets don't get sent too quickly
#ifdef WIN32 // !cj! TODO - should fix this up in windows
		 clock_t now = clock();
		 assert( CLOCKS_PER_SEC == 1000 );
		 while ( clock() <= now+10 ) { };
#else
		 usleep(10*1000);
#endif

}

//------------------------------------------------------------------------------
Socket  TStun::openPort( unsigned short port, unsigned int interfaceIp, TEventLogThread* elt )
{
   Socket fd;

   fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if ( fd == INVALID_SOCKET )
   {
      int err = getErrno();
      log(elt,"\nError: Could not create a UDP socket:" + inttostr(err));
      return INVALID_SOCKET;
   }

   struct sockaddr_in addr;
   memset((char*) &(addr),0, sizeof((addr)));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(port);

   if ( (interfaceIp != 0) &&
        ( interfaceIp != 0x100007f ) )
   {
      addr.sin_addr.s_addr = htonl(interfaceIp);
      log(elt,"\nBinding to interface " + bigendian_to_dot_str(htonl(interfaceIp)));
    }

   if ( bind( fd,(struct sockaddr*)&addr, sizeof(addr)) != 0 )
   {
      int e = getErrno();

      switch (e)
      {
         case 0:
         {
            log(elt,"\nError: Could not bind socket");
            return INVALID_SOCKET;
         }
         case EADDRINUSE:
         {
            log(elt,"\nError: EADDRINUSE Port " + inttostr(port) + " for receiving UDP is in use");
            return INVALID_SOCKET;
         }
         case EADDRNOTAVAIL:
         {
         log(elt,"\nError:  EADDRNOTAVAIL Cannot assign requested address");
         return INVALID_SOCKET;
         }
         default:
         {
            log(elt,"\nError: Could not bind UDP receive port Error=" + inttostr(e) + " " + strerror(e));
            return INVALID_SOCKET;
         }
      }
   }
   log(elt,"\nOpened port " + inttostr(port) + " with fd " + inttostr(fd));
   assert( fd != INVALID_SOCKET  );
   return fd;
}
//---------------------------------------------------------------------------

int stunRand()
{
   // return 32 bits of random stuff
  // assert( sizeof(int) == 4 );
   /*
   static bool init=false;
   if ( !init )
   {
      init = true;

      UInt64 tick;


#if defined(WIN32)
      volatile unsigned int lowtick=0,hightick=0;
      __asm
         {
            rdtsc
               mov lowtick, eax
               mov hightick, edx
               }
      tick = hightick;
      tick <<= 32;
      tick |= lowtick;
#elif defined(__GNUC__) && ( defined(__i686__) || defined(__i386__) )
      asm("rdtsc" : "=A" (tick));
#elif defined (__SUNPRO_CC) || defined( __sparc__ )
      tick = gethrtime();
#elif defined(__MACH__)
      int fd=open("/dev/random",O_RDONLY);
      read(fd,&tick,sizeof(tick));
      closesocket(fd);
#else
#     error Need some way to seed the random number generator
#endif
      int seed = int(tick);
#ifdef WIN32
      srand(seed);
#else
      srandom(seed);
#endif

   }
*/

#ifdef WIN32
//   assert( RAND_MAX == 0x7fff );

   randomize();

   int r1 = rand();
   int r2 = rand();

   int ret = (r1<<16) + r2;

   return ret;
#else
   return random();
#endif
}
//------------------------------------------------------------------------------
int __fastcall TStun::stunRandomPort()
{
   int min=0x4000;
   int max=0x7FFF;

   int ret = stunRand();
   ret = ret|min;
   ret = ret&max;

   return ret;
}
//---------------------------------------------------------------------------
void __fastcall TStun::StunClientProc(void* INIDATA,TSip* sip,TEventLogThread* elt)
{
TIniData* IniData = (TIniData*)INIDATA;
if(IniData->StunIniData.Addr.empty())
  {
  log(elt,"\nStunServer is not assigned\n");
  return;
  }
assert( sizeof(UInt8 ) == 1 );
assert( sizeof(UInt16) == 2 );
assert( sizeof(UInt32) == 4 );

   //initNetwork();
  // cout << "STUN client version " << STUN_VERSION << endl;

   int testNum = 0;
  // bool verbose = false;

   StunAddress4 stunServerAddr;
   stunServerAddr.addr=0;

   int srcPort=0;
   StunAddress4 sAddr[MAX_NIC];
   int retval[MAX_NIC];
   int numNic=0;

   for ( int i=0; i<MAX_NIC; i++ )
   {
      sAddr[i].addr=0;
      sAddr[i].port=0;
      retval[i]=0;
   }
   bool ret = stunParseServerName( (char*)IniData->StunIniData.Addr.c_str(), stunServerAddr,elt);
   if ( ret != true )
      {
       log(elt,"\n" + IniData->StunIniData.Addr + " is not a valid host name ");
       return;
      }

   if ( srcPort == 0 )
      srcPort = stunRandomPort();

   if ( numNic == 0 )
      numNic = 1;

   for ( int nic=0; nic<numNic; nic++ )
   {
      sAddr[nic].port=srcPort;
      if ( stunServerAddr.addr == 0 )
      {
      log(elt,"\nstunServerAddr.addr == 0");
      return;
      }

      if (testNum==0)
      {
         bool presPort=false;
         bool hairpin=false;

         NatType stype = stunNatType( stunServerAddr, &presPort, &hairpin,
                                      srcPort, &sAddr[nic],sip,elt);

         if ( nic == 0 )
         {
            log(elt,"\nPrimary: ");
         }
         else
         {
            log(elt,"\nSecondary: ");
         }

         switch (stype)
         {
            case StunTypeFailure:
               log(elt,"Some stun error detetecting NAT type");
	       retval[nic] = -1;
               exit(-1);
               break;
            case StunTypeUnknown:
               log(elt,"Some unknown type error detetecting NAT type");
	       retval[nic] = 0xEE;
               break;
            case StunTypeOpen:
               log(elt,"Open");
	       retval[nic] = 0x00;
               break;
            case StunTypeIndependentFilter:
               log(elt,"Independent Mapping, Independent Filter");
               if ( presPort ) log(elt,", preserves ports"); else log(elt,", random port");
               if ( hairpin  ) log(elt,", will hairpin"); else log(elt,", no hairpin");
               retval[nic] = 0x02;
               break;
            case StunTypeDependentFilter:
               log(elt,"Independedt Mapping, Address Dependendent Filter");
               if ( presPort ) log(elt,", preserves ports"); else log(elt,", random port");
               if ( hairpin  ) log(elt,", will hairpin"); else log(elt,", no hairpin");
               retval[nic] = 0x04;
               break;
            case StunTypePortDependedFilter:
               log(elt,"Indepndent Mapping, Port Dependent Filter");
               if ( presPort ) log(elt,", preserves ports"); else log(elt,", random port");
               if ( hairpin  ) log(elt,", will hairpin"); else log(elt,", no hairpin");
               retval[nic] = 0x06;
               break;
            case StunTypeDependentMapping:
               log(elt,"Dependent Mapping");
               if ( presPort ) log(elt,", preserves ports"); else log(elt,", random port");
               if ( hairpin  ) log(elt,", will hairpin"); else log(elt,", no hairpin");
               retval[nic] = 0x08;
               break;
            case StunTypeFirewall:
               log(elt,"Firewall");
               retval[nic] = 0x0A;
               break;
            case StunTypeBlocked:
               log(elt,"Blocked or could not reach STUN server");
               retval[nic] = 0x0C;
               break;
            default:
               log(elt,inttostr(stype) + " - Unkown NAT type");
               retval[nic] = 0x0E;  // Unknown NAT type
               break;
         }

         if (!hairpin)
         {
             retval[nic] |= 0x10;
         }

         if (presPort)
         {
             retval[nic] |= 0x01;
         }
      }
      else if (testNum==100)
      {
         Socket myFd = openPort(srcPort,sAddr[nic].addr,elt);

         StunMessage req;
         memset(&req, 0, sizeof(StunMessage));

         StunAtrString username;
         StunAtrString password;
         username.sizeValue = 0;
         password.sizeValue = 0;

         stunBuildReqSimple( &req, username,
                             false , false ,
                             0x0c );

         char buf[STUN_MAX_MESSAGE_SIZE];
         int len = STUN_MAX_MESSAGE_SIZE;

         len = stunEncodeMessage( req, buf, len, password,elt );
         log(elt,"\nAbout to send msg of len " + inttostr(len) + " to " + inttostr(stunServerAddr.addr));
         while (1)
         {
            for ( int i=0; i<100; i++ )
            {
               sendMessage( myFd,
                            buf, len,
                            stunServerAddr.addr,
                            stunServerAddr.port,elt );
            }
#ifdef WIN32 // !cj! TODO - should fix this up in windows
            clock_t now = clock();
            assert( CLOCKS_PER_SEC == 1000 );
            while ( clock() <= now+10 ) { };
#else
            usleep(10*1000);
#endif
         }
      }
      else if (testNum==-2)
      {
         const int numPort = 5;
         int fd[numPort];
         StunAddress4 mappedAddr;

         for( int i=0; i<numPort; i++ )
         {
            fd[i] = stunOpenSocket( stunServerAddr, &mappedAddr,
                                    (srcPort==0)?0:(srcPort+i), &sAddr[nic],sip,elt);
            log(elt,"Got port at " + inttostr(mappedAddr.port));
         }

         for( int i=0; i<numPort; i++ )
         {
            closesocket(fd[i]);
         }
      }
      else if (testNum==-1)
      {
         int fd3,fd4;
         StunAddress4 mappedAddr;

         bool ok = stunOpenSocketPair(stunServerAddr,
                                      &mappedAddr,
                                      &fd3,
                                      &fd4,
                                      srcPort,
                                      &sAddr[nic],
                                      sip,elt);
         if ( ok )
         {
            closesocket(fd3);
            closesocket(fd4);
            cout << "Got port pair at " << mappedAddr.port << endl;
         }
         else
         {
            cerr << "Opened a stun socket pair FAILED" << endl;
         }
      }
      else
      {
         stunTest( stunServerAddr,testNum,&(sAddr[nic]),sip,elt );
      }
   } // end of for loop
  // cout << endl;


   UInt32 ret_1=0;
   for ( int i=numNic-1; i>=0; i-- )
   {
      if ( retval[i] == -1 )
      {
         ret_1 = 0xFFFFFFFF;
         break;
      }
      ret_1 = ret_1 << 8;
      ret_1 = ret_1 | ( retval[i] & 0xFF );
   }

   /*
   cout << "Return value is " << hex << "0x";
   cout.fill('0');
   cout.width(6);
   cout << ret << dec << endl;
   cout.fill(' ');
   */

}
//---------------------------------------------------------------------------

bool __fastcall TStun::stunParseHostName( char* peerName,UInt32& ip, UInt16& portVal,UInt16 defaultPort,TEventLogThread* elt )
{
   in_addr sin_addr;

   char host[512];
   strncpy(host,peerName,512);
   host[512-1]='\0';
   char* port = NULL;

   int portNum = defaultPort;

   // pull out the port part if present.
   char* sep = strchr(host,':');

   if ( sep == NULL )
   {
      portNum = defaultPort;
   }
   else
   {
      *sep = '\0';
      port = sep + 1;
      // set port part

      char* endPtr=NULL;

      portNum = strtol(port,&endPtr,10);

      if ( endPtr != NULL )
      {
         if ( *endPtr != '\0' )
         {
            portNum = defaultPort;
         }
      }
   }

   if ( portNum < 1024 ) return false;
   if ( portNum >= 0xFFFF ) return false;

   // figure out the host part
   struct hostent* h;

#ifdef WIN32
   assert( strlen(host) >= 1 );
   if ( isdigit( host[0] ) )
   {
      // assume it is a ip address
      unsigned long a = inet_addr(host);

      ip = ntohl( a );
   }
   else
   {
      // assume it is a host name
      h = gethostbyname( host );

      if ( h == NULL )
      {
         int err = getErrno();
         log(elt,"\nError: gethostbyname()==NULL");

         assert( err != WSANOTINITIALISED );

         ip = ntohl( 0x7F000001L );

         return false;
      }
      else
      {
         sin_addr = *(struct in_addr*)h->h_addr;
         ip = ntohl( sin_addr.s_addr );
      }
   }

#else
   h = gethostbyname( host );
   if ( h == NULL )
   {
      int err = getErrno();
      log(elt,"\nError: " + intostr(err));
      ip = ntohl( 0x7F000001L );
      return false;
   }
   else
   {
      sin_addr = *(struct in_addr*)h->h_addr;
      ip = ntohl( sin_addr.s_addr );
   }
#endif

   portVal = portNum;

   return true;
}
//------------------------------------------------------------------------------
bool __fastcall TStun::stunParseServerName( char* name, StunAddress4& addr,TEventLogThread* elt)
{
   assert(name);

   // TODO - put in DNS SRV stuff.

   bool ret = stunParseHostName( name, addr.addr, addr.port, 3478,elt);
   if ( ret != true )
   {
       addr.port=0xFFFF;
   }
   return ret;
}
//------------------------------------------------------------------------------
char* TStun::encode(char* buf, const char* data, unsigned int length)
{
   memcpy(buf, data, length);
   return buf + length;
}
//----------------------------------------------------------------------------
char* TStun::encode16(char* buf, UInt16 data)
{
   UInt16 ndata = htons(data);
   memcpy(buf, reinterpret_cast<void*>(&ndata), sizeof(UInt16));
   return buf + sizeof(UInt16);
}
//---------------------------------------------------------------------------
void __fastcall TStun::log(TEventLogThread* elt,const string& s)
{
if(elt)
   if(elt->getlog())
      elt->FputEvt(s);
}
//------------------------------------------------------------------------------
char* TStun::encode32(char* buf, UInt32 data)
{
   UInt32 ndata = htonl(data);
   memcpy(buf, reinterpret_cast<void*>(&ndata), sizeof(UInt32));
   return buf + sizeof(UInt32);
}
//---------------------------------------------------------------------------
char* TStun::encodeAtrAddress4(char* ptr, UInt16 type, const StunAtrAddress4& atr)
{
   ptr = encode16(ptr, type);
   ptr = encode16(ptr, 8);
   *ptr++ = atr.pad;
   *ptr++ = IPv4Family;
   ptr = encode16(ptr, atr.ipv4.port);
   ptr = encode32(ptr, atr.ipv4.addr);

   return ptr;
}
//------------------------------------------------------------------------------
char* TStun::encodeAtrChangeRequest(char* ptr, const StunAtrChangeRequest& atr)
{
   ptr = encode16(ptr, ChangeRequest);
   ptr = encode16(ptr, 4);
   ptr = encode32(ptr, atr.value);
   return ptr;
}
//---------------------------------------------------------------------------
char* TStun::encodeAtrError(char* ptr, const StunAtrError& atr)
{
   ptr = encode16(ptr, ErrorCode);
   ptr = encode16(ptr, 6 + atr.sizeReason);
   ptr = encode16(ptr, atr.pad);
   *ptr++ = atr.errorClass;
   *ptr++ = atr.number;
   ptr = encode(ptr, atr.reason, atr.sizeReason);
   return ptr;
}
//-----------------------------------------------------------------------------
char* TStun::encodeAtrString(char* ptr, UInt16 type, const StunAtrString& atr)
{
   assert(atr.sizeValue % 4 == 0);

   ptr = encode16(ptr, type);
   ptr = encode16(ptr, atr.sizeValue);
   ptr = encode(ptr, atr.value, atr.sizeValue);
   return ptr;
}
//---------------------------------------------------------------------------
char* TStun::encodeAtrUnknown(char* ptr, const StunAtrUnknown& atr)
{
   ptr = encode16(ptr, UnknownAttribute);
   ptr = encode16(ptr, 2+2*atr.numAttributes);
   for (int i=0; i<atr.numAttributes; i++)
   {
      ptr = encode16(ptr, atr.attrType[i]);
   }
   return ptr;
}
//---------------------------------------------------------------------------
#ifdef NOSSL
void TStun::computeHmac(char* hmac, const char* input, int length, const char* key, int sizeKey)
{
   strncpy(hmac,"hmac-not-implemented",20);
}
#else
void TStun::computeHmac(char* hmac, const char* input, int length, const char* key, int sizeKey)
{
   unsigned int resultSize=0;
   HMAC(EVP_sha1(),
        key, sizeKey,
        reinterpret_cast<const unsigned char*>(input), length,
        reinterpret_cast<unsigned char*>(hmac), &resultSize);
   assert(resultSize == 20);
}
#endif
//---------------------------------------------------------------------------
char* TStun::encodeXorOnly(char* ptr)
{
   ptr = encode16(ptr, XorOnly );
   return ptr;
}
//---------------------------------------------------------------------------
char* TStun::encodeAtrIntegrity(char* ptr, const StunAtrIntegrity& atr)
{
   ptr = encode16(ptr, MessageIntegrity);
   ptr = encode16(ptr, 20);
   ptr = encode(ptr, atr.hash, sizeof(atr.hash));
   return ptr;
}
//---------------------------------------------------------------------------
unsigned int __fastcall TStun::stunEncodeMessage( const StunMessage& msg,
                   char* buf,
                   unsigned int bufLen,
                   const StunAtrString& password,
                   TEventLogThread* elt)
{
   assert(bufLen >= sizeof(StunMsgHdr));
   char* ptr = buf;

   ptr = encode16(ptr, msg.msgHdr.msgType);
   char* lengthp = ptr;
   ptr = encode16(ptr, 0);
   ptr = encode(ptr, reinterpret_cast<const char*>(msg.msgHdr.id.octet), sizeof(msg.msgHdr.id));

   log(elt,"\nEncoding stun message: ");
   if (msg.hasMappedAddress)
   {
      log(elt,"\nEncoding MappedAddress: " + littleendian_to_dot_str(msg.mappedAddress.ipv4.addr));
      ptr = encodeAtrAddress4 (ptr, MappedAddress, msg.mappedAddress);
   }
   if (msg.hasResponseAddress)
   {
      log(elt,"\nEncoding ResponseAddress: " + littleendian_to_dot_str(msg.responseAddress.ipv4.addr));
      ptr = encodeAtrAddress4(ptr, ResponseAddress, msg.responseAddress);
   }
   if (msg.hasChangeRequest)
   {
      log(elt,"\nEncoding ChangeRequest: " + inttostr(msg.changeRequest.value));
      ptr = encodeAtrChangeRequest(ptr, msg.changeRequest);
   }
   if (msg.hasSourceAddress)
   {
      log(elt,"\nEncoding SourceAddress: " + littleendian_to_dot_str(msg.sourceAddress.ipv4.addr));
      ptr = encodeAtrAddress4(ptr, SourceAddress, msg.sourceAddress);
   }
   if (msg.hasChangedAddress)
   {
      log(elt,"\nEncoding ChangedAddress: " + littleendian_to_dot_str(msg.changedAddress.ipv4.addr));
      ptr = encodeAtrAddress4(ptr, ChangedAddress, msg.changedAddress);
   }
   if (msg.hasUsername)
   {
      log(elt,"\nEncoding Username: " + string(msg.username.value));
      ptr = encodeAtrString(ptr, Username, msg.username);
   }
   if (msg.hasPassword)
   {
      log(elt,"\nEncoding Password: " + string(msg.password.value));
      ptr = encodeAtrString(ptr, Password, msg.password);
   }
   if (msg.hasErrorCode)
   {
      log(elt,"\nEncoding ErrorCode: class=" + inttostr(msg.errorCode.errorClass) + (string)" number=" + inttostr(msg.errorCode.number)
			+ " reason=" + string(msg.errorCode.reason));
      ptr = encodeAtrError(ptr, msg.errorCode);
   }
   if (msg.hasUnknownAttributes)
   {
      log(elt,"\nEncoding UnknownAttribute: ???");
      ptr = encodeAtrUnknown(ptr, msg.unknownAttributes);
   }
   if (msg.hasReflectedFrom)
   {
      log(elt,"\nEncoding ReflectedFrom: " + littleendian_to_dot_str(msg.reflectedFrom.ipv4.addr));
      ptr = encodeAtrAddress4(ptr, ReflectedFrom, msg.reflectedFrom);
   }
   if (msg.hasXorMappedAddress)
   {
      log(elt,"\nEncoding XorMappedAddress: " + littleendian_to_dot_str(msg.xorMappedAddress.ipv4.addr));
      ptr = encodeAtrAddress4 (ptr, XorMappedAddress, msg.xorMappedAddress);
   }
   if (msg.xorOnly)
   {
      log(elt,"\nEncoding xorOnly: ");
      ptr = encodeXorOnly( ptr );
   }
   if (msg.hasServerName)
   {
      log(elt,"\nEncoding ServerName: " + string(msg.serverName.value));
      ptr = encodeAtrString(ptr, ServerName, msg.serverName);
   }
   if (msg.hasSecondaryAddress)
   {
      log(elt,"\nEncoding SecondaryAddress: " + littleendian_to_dot_str(msg.secondaryAddress.ipv4.addr));
      ptr = encodeAtrAddress4 (ptr, SecondaryAddress, msg.secondaryAddress);
   }

   if (password.sizeValue > 0)
   {
      log(elt,"\nHMAC with password: " + string(password.value));

      StunAtrIntegrity integrity;
      computeHmac(integrity.hash, buf, int(ptr-buf) , password.value, password.sizeValue);
      ptr = encodeAtrIntegrity(ptr, integrity);
   }
   
   encode16(lengthp, UInt16(ptr - buf - sizeof(StunMsgHdr)));
   return int(ptr - buf);
}
//---------------------------------------------------------------------------
bool TStun::sendMessage( Socket fd, char* buf, int l,
             unsigned int dstIp, unsigned short dstPort,
             TEventLogThread* elt)
{
   assert( fd != INVALID_SOCKET );

   int s;
   if ( dstPort == 0 )
   {
      // sending on a connected port
      assert( dstIp == 0 );

      s = send(fd,buf,l,0);
   }
   else
   {
      assert( dstIp != 0 );
      assert( dstPort != 0 );

      struct sockaddr_in to;
      int toLen = sizeof(to);
      memset(&to,0,toLen);

      to.sin_family = AF_INET;
      to.sin_port = htons(dstPort);
      to.sin_addr.s_addr = htonl(dstIp);

      s = sendto(fd, buf, l, 0,(sockaddr*)&to, toLen);
   }

   if ( s == SOCKET_ERROR )
   {
      int e = getErrno();
      switch (e)
      {
         case ECONNREFUSED:
         case EHOSTDOWN:
         case EHOSTUNREACH:
         {
            // quietly ignore this
         }
         break;
         case EAFNOSUPPORT:
            log(elt,"\nError: EAFNOSUPPORT in send");
            break;
         default:log(elt,"\nError: " + inttostr(e) + " "  + strerror(e) + " in send");
      }
      return false;
   }

   if ( s == 0 )
   {
      log(elt,"\nno data sent in send");
      return false;
   }

   if ( s != l )
   {
    log(elt,"\nError: only " + inttostr(s) + (string)" out of " + inttostr(l) + " bytes sent");
    return false;
   }

   return true;
}
//-----------------------------------------------------------------------------
bool TStun::stunParseAtrChangeRequest( char* body, unsigned int hdrLen,  StunAtrChangeRequest& result,TEventLogThread* elt )
{
   if ( hdrLen != 4 )
   {
      log(elt,"\nhdr length = " + inttostr(hdrLen) + " expecting " + inttostr(sizeof(result)));
      log(elt,"\nIncorrect size for ChangeRequest");
      return false;
   }
   else
   {
      memcpy(&result.value, body, 4);
      result.value = ntohl(result.value);
      return true;
   }
}
//---------------------------------------------------------------------------
bool  TStun::stunParseAtrAddress( char* body, unsigned int hdrLen,  StunAtrAddress4& result,TEventLogThread* elt )
{
   if ( hdrLen != 8 )
   {
      log(elt,"\nhdrLen wrong for Address");
      return false;
   }
   result.pad = *body++;
   result.family = *body++;
   if (result.family == IPv4Family)
   {
      UInt16 nport;
      memcpy(&nport, body, 2); body+=2;
      result.ipv4.port = ntohs(nport);

      UInt32 naddr;
      memcpy(&naddr, body, 4); body+=4;
      result.ipv4.addr = ntohl(naddr);
      return true;
   }
   else if (result.family == IPv6Family)
   {
      log(elt,"\nipv6 not supported");
   }
   else
   {
      log(elt,"\nbad address family: " + inttostr(result.family));
   }

   return false;
}
//------------------------------------------------------------------------------
bool TStun::stunParseAtrString( char* body, unsigned int hdrLen,  StunAtrString& result, TEventLogThread* elt )
{
   if ( hdrLen >= STUN_MAX_STRING )
   {
      log(elt,"\nString is too large");
      return false;
   }
   else
   {
      if (hdrLen % 4 != 0)
      {
         log(elt,"\nBad length string " + inttostr(hdrLen));
         return false;
      }

      result.sizeValue = hdrLen;
      memcpy(&result.value, body, hdrLen);
      result.value[hdrLen] = 0;
      return true;
   }
}
//------------------------------------------------------------------------------
bool TStun::stunParseAtrIntegrity( char* body, unsigned int hdrLen,  StunAtrIntegrity& result,TEventLogThread* elt )
{
   if ( hdrLen != 20)
   {
      log(elt,"\nMessageIntegrity must be 20 bytes");
      return false;
   }
   else
   {
      memcpy(&result.hash, body, hdrLen);
      return true;
   }
}
//---------------------------------------------------------------------------
bool TStun::stunParseAtrUnknown( char* body, unsigned int hdrLen,  StunAtrUnknown& result,TEventLogThread* elt )
{
   if ( hdrLen >= sizeof(result) )
   {
      return false;
   }
   else
   {
      if (hdrLen % 4 != 0) return false;
      result.numAttributes = hdrLen / 4;
      for (int i=0; i<result.numAttributes; i++)
      {
         memcpy(&result.attrType[i], body, 2); body+=2;
         result.attrType[i] = ntohs(result.attrType[i]);
      }
      return true;
   }
}

//---------------------------------------------------------------------------
bool TStun::stunParseAtrError( char* body, unsigned int hdrLen,  StunAtrError& result, TEventLogThread* elt )
{
   if ( hdrLen >= sizeof(result) )
   {
      log(elt,"\nhead on Error too large");
      return false;
   }
   else
   {
      memcpy(&result.pad, body, 2); body+=2;
      result.pad = ntohs(result.pad);
      result.errorClass = *body++;
      result.number = *body++;

      result.sizeReason = hdrLen - 4;
      memcpy(&result.reason, body, result.sizeReason);
      result.reason[result.sizeReason] = 0;
      return true;
   }
}
//---------------------------------------------------------------------------
void TStun::stunBuildReqSimple( StunMessage* msg,
                    const StunAtrString& username,
                    bool changePort, bool changeIp, unsigned int id )
{
   assert( msg );
   memset( msg , 0 , sizeof(*msg) );

   msg->msgHdr.msgType = BindRequestMsg;

   for ( int i=0; i<16; i=i+4 )
   {
      assert(i+3<16);
      int r = stunRand();
      msg->msgHdr.id.octet[i+0]= r>>0;
      msg->msgHdr.id.octet[i+1]= r>>8;
      msg->msgHdr.id.octet[i+2]= r>>16;
      msg->msgHdr.id.octet[i+3]= r>>24;
   }

   if ( id != 0 )
   {
      msg->msgHdr.id.octet[0] = id;
   }

   msg->hasChangeRequest = true;
   msg->changeRequest.value =(changeIp?ChangeIpFlag:0) |
      (changePort?ChangePortFlag:0);

   if ( username.sizeValue > 0 )
   {
      msg->hasUsername = true;
      msg->username = username;
   }
}
//---------------------------------------------------------------------------
void TStun::stunTest( StunAddress4& dest, int testNum, StunAddress4* sAddr,TSip* sip,TEventLogThread* elt )
{
   assert( dest.addr != 0 );
   assert( dest.port != 0 );

   int port = stunRandomPort();
   UInt32 interfaceIp=0;
   if (sAddr)
   {
      interfaceIp = sAddr->addr;
      if ( sAddr->port != 0 )
      {
        port = sAddr->port;
      }
   }
   Socket myFd = openPort(port,interfaceIp,elt);

   StunAtrString username;
   StunAtrString password;

   username.sizeValue = 0;
   password.sizeValue = 0;

#ifdef USE_TLS
   stunGetUserNameAndPassword( dest, username, password );
#endif

   stunSendTest( myFd, dest, username, password, testNum, elt );

   char msg[STUN_MAX_MESSAGE_SIZE];
   int msgLen = STUN_MAX_MESSAGE_SIZE;

   StunAddress4 from;
   getMessage( myFd,
               msg,
               &msgLen,
               &from.addr,
               &from.port,elt );

   StunMessage resp;
   memset(&resp, 0, sizeof(StunMessage));

   log(elt,"\nGot a response");
   bool ok = stunParseMessage( msg,msgLen, resp,sip,elt );

   log(elt,"\nok=" + inttostr(ok));
   string octstr;
   for(int i=0;i<16;i++)
       octstr += inttohexstr(resp.msgHdr.id.octet[i]);
   log(elt,"\nid=" + octstr);
   log(elt,"\nmappedAddr=" + littleendian_to_dot_str(resp.mappedAddress.ipv4.addr));
   log(elt,"\nchangedAddr=" + littleendian_to_dot_str(resp.changedAddress.ipv4.addr));
   if (sAddr)
     {
      sAddr->port = resp.mappedAddress.ipv4.port;
      sAddr->addr = resp.mappedAddress.ipv4.addr;
     }
}
//---------------------------------------------------------------------------
int TStun::stunOpenSocket( StunAddress4& dest, StunAddress4* mapAddr,
                int port, StunAddress4* srcAddr,TSip* sip,TEventLogThread* elt)
{
   assert( dest.addr != 0 );
   assert( dest.port != 0 );
   assert( mapAddr );

   if ( port == 0 )
   {
      port = stunRandomPort();
   }
   unsigned int interfaceIp = 0;
   if ( srcAddr )
   {
      interfaceIp = srcAddr->addr;
   }

   Socket myFd = openPort(port,interfaceIp,elt);
   if (myFd == INVALID_SOCKET)
   {
      return myFd;
   }

   char msg[STUN_MAX_MESSAGE_SIZE];
   int msgLen = sizeof(msg);

   StunAtrString username;
   StunAtrString password;

   username.sizeValue = 0;
   password.sizeValue = 0;

#ifdef USE_TLS
   stunGetUserNameAndPassword( dest, username, password );
#endif

   stunSendTest(myFd, dest, username, password, 1, 0/*false*/ );

   StunAddress4 from;

   getMessage( myFd, msg, &msgLen, &from.addr, &from.port,elt);

   StunMessage resp;
   memset(&resp, 0, sizeof(StunMessage));

   bool ok = stunParseMessage( msg, msgLen, resp,sip,elt);
   if (!ok)
   {
      return -1;
   }

   StunAddress4 mappedAddr = resp.mappedAddress.ipv4;
   //StunAddress4 changedAddr = resp.changedAddress.ipv4;

   //clog << "--- stunOpenSocket --- " << endl;
   //clog << "\treq  id=" << req.id << endl;
   //clog << "\tresp id=" << id << endl;
   //clog << "\tmappedAddr=" << mappedAddr << endl;

   *mapAddr = mappedAddr;

   return myFd;
}
//----------------------------------------------------------------------------
bool TStun::stunOpenSocketPair( StunAddress4& dest, StunAddress4* mapAddr,
                    int* fd1, int* fd2,
                    int port, StunAddress4* srcAddr,
                    TSip* sip,TEventLogThread* elt )
{
   assert( dest.addr!= 0 );
   assert( dest.port != 0 );
   assert( mapAddr );

   const int NUM=3;

   if ( port == 0 )
   {
      port = stunRandomPort();
   }

   *fd1=-1;
   *fd2=-1;

   char msg[STUN_MAX_MESSAGE_SIZE];
   int msgLen =sizeof(msg);

   StunAddress4 from;
   int fd[NUM];
   int i;

   unsigned int interfaceIp = 0;
   if ( srcAddr )
   {
      interfaceIp = srcAddr->addr;
   }

   for( i=0; i<NUM; i++)
   {
      fd[i] = openPort( (port == 0) ? 0 : (port + i),
                        interfaceIp, elt);
      if (fd[i] < 0)
      {
         while (i > 0)
         {
            closesocket(fd[--i]);
         }
         return false;
      }
   }

   StunAtrString username;
   StunAtrString password;

   username.sizeValue = 0;
   password.sizeValue = 0;

#ifdef USE_TLS
   stunGetUserNameAndPassword( dest, username, password );
#endif

   for( i=0; i<NUM; i++)
   {
      stunSendTest(fd[i], dest, username, password, 1/*testNum*/, elt );
   }

   StunAddress4 mappedAddr[NUM];
   for( i=0; i<NUM; i++)
   {
      msgLen = sizeof(msg)/sizeof(*msg);
      getMessage( fd[i],
                  msg,
                  &msgLen,
                  &from.addr,
                  &from.port ,elt);

      StunMessage resp;
      memset(&resp, 0, sizeof(StunMessage));

      bool ok = stunParseMessage( msg, msgLen, resp,sip,elt);
      if (!ok)
      {
         return false;
      }

      mappedAddr[i] = resp.mappedAddress.ipv4;
     // StunAddress4 changedAddr = resp.changedAddress.ipv4;
   }

      log(elt,"\n--- stunOpenSocketPair --- ");
      for( i=0; i<NUM; i++)
         log(elt,"\nmappedAddr=" + littleendian_to_dot_str(mappedAddr[i].addr));

   if ( mappedAddr[0].port %2 == 0 )
   {
      if (  mappedAddr[0].port+1 ==  mappedAddr[1].port )
      {
         *mapAddr = mappedAddr[0];
         *fd1 = fd[0];
         *fd2 = fd[1];
         closesocket( fd[2] );
         return true;
      }
   }
   else
   {
      if (( mappedAddr[1].port %2 == 0 )
          && (  mappedAddr[1].port+1 ==  mappedAddr[2].port ))
      {
         *mapAddr = mappedAddr[1];
         *fd1 = fd[1];
         *fd2 = fd[2];
         closesocket( fd[0] );
         return true;
      }
   }

   // something failed, close all and return error
   for( i=0; i<NUM; i++)
   {
      closesocket( fd[i] );
   }

   return false;
}
//------------------------------------------------------------------------------
