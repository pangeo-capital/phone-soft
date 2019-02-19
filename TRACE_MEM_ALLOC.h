#ifndef Exs_RTL__TRACE_MEM_ALLOC_H
#define Exs_RTL__TRACE_MEM_ALLOC_H

//************************************************************************
#ifdef TRACE_ALLOC_MEM
#ifdef _DEBUG

typedef struct {
    DWORD       address;
    DWORD	size;
    string      file;
    DWORD	line;
} ALLOC_INFO;

//---------------------------------------------------------------------------
class TALLOC_INFO_STRUCT{
public:
bool AL_BLOCK;
CRITICAL_SECTION ais_cs;
typedef map < DWORD, ALLOC_INFO > TAllocList;
TAllocList AL;
TALLOC_INFO_STRUCT(){
                  ::InitializeCriticalSection(&ais_cs);
                    AL_BLOCK = false;
                    }
virtual ~TALLOC_INFO_STRUCT(){
                    ::DeleteCriticalSection(&ais_cs);
                    }
};
//---------------------------------------------------------------------------

void AddTrack(DWORD addr,  DWORD asize, const char *fname, DWORD lnum);
void RemoveTrack(DWORD addr);
void DUMP_UNFREED();

inline void * __cdecl operator new(unsigned int size, const char *file, int line);
inline void   __cdecl operator delete(void *p);

inline void * __cdecl operator new[](unsigned int size, const char *file, int line);
inline void   __cdecl operator delete[](void *p);


void * __cdecl operator new(unsigned int size, const char *file, int line)
{
void *ptr = (void *)malloc(size);
AddTrack((DWORD)ptr, size, file, line);
return ptr;
}

inline void * __cdecl operator new[] (size_t size, const char *file, int line)
{
void *ptr = (void *)malloc(size);
AddTrack((DWORD)ptr, size, file, line);
return ptr;
}

inline void __cdecl operator delete(void *p) {
RemoveTrack((DWORD)p);
free(p);
}

inline void __cdecl operator delete[] (void *p) {
RemoveTrack((DWORD)p);
free(p);
}
#endif //#ifdef _DEBUG

#ifdef _DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#define new DEBUG_NEW

#endif //#ifdef TRACE_ALLOC_MEM
//------------------------------------------------------------------------------
#endif //#ifndef Exs_RTL__TRACE_MEM_ALLOC_H

