#ifndef cache_db_h
#define cache_db_h

#ifdef CACHE_DB_LIBS_EXPORTS
#define CACHE_DB_API __declspec(dllexport)
#else
#define CACHE_DB_API __declspec(dllimport)
#endif

typedef void (*def_complete) ();

typedef void* CACHE_HANDLE;

#define CACHE_INVALID_HANDLE 0

typedef enum {CACHE_TYPE_Unknown, CACHE_TYPE_String, CACHE_TYPE_Integer, CACHE_TYPE_Double, CACHE_TYPE_Bool, CACHE_TYPE_DateTime, CACHE_TYPE_Char, CACHE_TYPE_Short, CACHE_TYPE_Int64, CACHE_TYPE_Float} CacheFieldType;

#ifdef __cplusplus
extern "C" {
#endif

  CACHE_DB_API void __stdcall cacheInitCacheDb(const char* connectString);

  CACHE_DB_API void __stdcall cacheDestroyCacheDb();

  // Set callback function 
  CACHE_DB_API void __stdcall cacheSetHandlerComplete(def_complete handler);

  CACHE_DB_API void __stdcall cacheLoad(const char* tableName, const char* sqlFileName, const char* idxAdd="");

  CACHE_DB_API CACHE_HANDLE __stdcall cacheLock(const char* tableName, bool isWritable=false, int index=0);
  
  CACHE_DB_API void __stdcall cacheUnlock(CACHE_HANDLE handle);

  CACHE_DB_API unsigned short __stdcall cacheGetData(CACHE_HANDLE handle, const char* fieldName, void* buf, unsigned short* bufLen=0, unsigned short* fieldType=0);

  CACHE_DB_API bool __stdcall cacheLocate(CACHE_HANDLE handle, void* buf);

  CACHE_DB_API void __stdcall cacheStartUpdate(CACHE_HANDLE handle);

  CACHE_DB_API void __stdcall cacheStartInsert(CACHE_HANDLE handle);

  CACHE_DB_API void __stdcall cachePutData(CACHE_HANDLE handle, const char* fieldName, void* buf, unsigned short* bufLen, bool update_db=false);

  CACHE_DB_API void __stdcall cacheCommitUpdate(CACHE_HANDLE handle);

  CACHE_DB_API void __stdcall cacheCommitInsert(CACHE_HANDLE handle);

  CACHE_DB_API void __stdcall cacheFirst(CACHE_HANDLE handle);
  CACHE_DB_API void __stdcall cacheLast(CACHE_HANDLE handle);
  CACHE_DB_API void __stdcall cacheNext(CACHE_HANDLE handle);
  CACHE_DB_API bool __stdcall cacheEof(CACHE_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif