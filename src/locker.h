//---------------------------------------------------------------------------

#ifndef lockerH
#define lockerH
#include <vcl.h>

//---------------------------------------------------------------------------
struct locker_cs {
  CRITICAL_SECTION& cs;
  bool is_lock_active;
  locker_cs(CRITICAL_SECTION& lock_obj)
    : cs(lock_obj), is_lock_active(false) {
    lock();
  }
  ~locker_cs() {
    unlock();
  }
  void lock() {
    if (is_lock_active)
      return;
    ::EnterCriticalSection(&cs);
    is_lock_active = true;
  }
  void unlock() {
    if (!is_lock_active)
      return;
    ::LeaveCriticalSection(&cs);
    is_lock_active = false;
  }
};
#endif
