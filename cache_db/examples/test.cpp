#include <iostream>
#include "windows.h"
#include "cache_db.h"


bool complete=false;

void evt_load_complete () {
  std::cout << "evt_load_complete" << std::endl;
  complete=true;
}

int main () {
  cacheInitCacheDb("DRIVER={Microsoft Paradox Driver (*.db )};DefaultDir=c:\\ExternalDB;Threads=3;");
  //cacheInitCacheDb("FILEDSN=c:\\ExternalDB\\ExtLst.DB.dsn");
  cacheSetHandlerComplete(evt_load_complete);
  cacheLoad("ExtLst", "select top 100 * from ExtLst");
  while (!complete) { Sleep(10); }
  CACHE_HANDLE h=cacheLock("ExtLst", true);
  if (h==CACHE_INVALID_HANDLE)
    return 0;
  const char* str="andreyt";
  char buf[255];
  unsigned short ft=0;
  unsigned short len=255;
  if (cacheLocate(h, (void*)str)) {
    cacheGetData(h, "HostName", &buf, &len, &ft); len=255; std::cout << std::string(buf,len).c_str() << " " << len << " " << ft << std::endl;
    cacheGetData(h, "Codec", &buf, &len, &ft); len=255; std::cout << std::string(buf,len).c_str() << " " << len << " " << ft << std::endl;
    cacheGetData(h, "Profile", &buf, &len, &ft);  std::cout << std::string(buf,len).c_str() << " " << len << " " << ft << std::endl;
    cacheGetData(h, "Auth", &buf, &len, &ft);     std::cout << *(int*)buf << " " << len << " " << ft << std::endl;
    int tmp=*(int*)buf;
    tmp++;
    cacheStartUpdate(h);
    cachePutData(h, "Auth", &tmp, &len, true);
    cachePutData(h, "Expires", &tmp, &len, true);
    cacheCommitUpdate(h);
    cacheGetData(h, "Auth", &buf, &len, &ft);  std::cout << *(int*)buf << " " << len << " " << ft << std::endl;

    cacheStartInsert(h);
    char n[]="new_user_name1";
    len=14;
    cachePutData(h, "UserName", &n, &len, true);
    len=255;
    cacheGetData(h, "UserName", &buf, &len, &ft); std::cout << std::string(buf, len).c_str() << " " << len << " " << ft << std::endl;
    len=4;
    cachePutData(h, "Auth", &tmp, &len, true);
    len=4;
    cachePutData(h, "Expires", &tmp, &len, true);
    cacheCommitInsert(h);
  }
  std::cout << "*******" << std::endl;
  cacheLast(h);
  len=255;
  cacheGetData(h, "UserName", &buf, &len, &ft); std::cout << std::string(buf,len).c_str() << ";" << std::endl;
  cacheFirst(h);
  while (!cacheEof(h)) {
    len=255;
    cacheGetData(h, "UserName", &buf, &len, &ft); std::cout << std::string(buf,len).c_str() << ";";
    len=255;
    cacheGetData(h, "HostName", &buf, &len, &ft); std::cout << std::string(buf,len).c_str();
    std::cout << std::endl;
    cacheNext(h);
  }
  cacheUnlock(h);
  Sleep(100);
  cacheDestroyCacheDb();
}

