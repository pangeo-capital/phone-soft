//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "SipRecvThread.h"
#include "utils.h"
#include "Sip.h"
#include "ParallelPhone_Unit.h"

#pragma package(smart_init)
//----------------------------------------------------------------------------
void __fastcall TSipRecvThread::Execute()
{
try{
while(!Terminated)
     {
     TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
     if(opb)
       {
       struct sockaddr_in from;
       int fromlen = sizeof(from);
       memset(&from,0,sizeof(from));
       int bread = recvfrom(sck,rcvbuf,SIP_MAX_PACKET,0,(struct sockaddr*)&from,&fromlen);
       if(!opb)
         {
         lasterr = " Error: opb = NULL";
         sendlasterr();
         continue;
         }
       if(get_thread_block())
         {
         delete opb;
         continue;
         }
       if(bread == SOCKET_ERROR){
         if(Terminated)
           {
           delete opb;
           return;
           }
         int err = WSAGetLastError();
         lasterr = "TSipRecvThread::Execute()  bread == SOCKET_ERROR";
         GetLastSocketError(lasterr,err);
         sendlasterr();
         switch(err){
               case WSAECONNRESET:{
                    break;
                    }
               }
         delete opb;
         continue;
         }
       char* pAddr = inet_ntoa(from.sin_addr);
       if(pAddr)
          opb->FromIP = string(pAddr);
       opb->FromPort = htons(from.sin_port);
       opb->s.resize(bread);
       if(opb->s.size() < (unsigned)(bread))
         {
         lasterr = " Allocated buf < bread";
         sendlasterr();
         delete opb;
         continue;
         }
       memcpy(&opb->s[0],rcvbuf,bread);
       opb->datasize = bread; //for non string content
       opb->getDateTime();
       if(Sip->spt)
         {
         bool a = false;
         Sip->spt->setQueue(opb);
         updateSentQueue(opb, a);
         }
       else
          delete opb;
       }
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipRecvThread::Execute",e);}
}
//-----------------------------------------------------------------------------
//-------------- For parallel phone -------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TSipRecvThread_PPH::Execute()
{
try{
while(!Terminated)
     {
     if(sck == INVALID_SOCKET)
       {
       ::Sleep(10);
       continue;
       }
     TOutPutUdpBlock* opb = new TOutPutUdpBlock(pktn);
     if(opb)
       {
       opb->parallel_phone = true;
       struct sockaddr_in from;
       int fromlen = sizeof(from);
       memset(&from,0,sizeof(from));
       int bread = recvfrom(sck,rcvbuf,SIP_MAX_PACKET,0,(struct sockaddr*)&from,&fromlen);
       if(get_thread_block())
         {
         delete opb;
         continue;
         }
       if(bread == SOCKET_ERROR){
         if(Terminated)
           {
           delete opb;
           return;
           }
         int err = WSAGetLastError();
         lasterr = "TSipRecvThread::Execute()  bread == SOCKET_ERROR";
         GetLastSocketError(lasterr,err);
         sendlasterr();
         switch(err){
               case WSAECONNRESET:{
                    break;
                    }
               }
         delete opb;
         continue;
         }
       char* pAddr = inet_ntoa(from.sin_addr);
       if(pAddr)
          opb->FromIP = string(pAddr);
       opb->FromPort = htons(from.sin_port);
       opb->s.resize(bread);
       if(opb->s.size() < (unsigned)(bread))
         {
         lasterr = " Allocated buf < bread";
         sendlasterr();
         delete opb;
         continue;
         }
       memcpy(&opb->s[0],rcvbuf,bread);
       opb->datasize = bread; //for non string content
       opb->getDateTime();
       if(pps->spt_pph)
         {
         bool a = false;
         pps->spt_pph->setQueue(opb);
         updateSentQueue(opb, a);
         }
       else
          delete opb;
       }
     }
 }//try
catch(Exception& e){exsSstEXCEPTION(*eltp,"__TSipRecvThread_PPH::Execute",e);}
}
//-----------------------------------------------------------------------------

