#ifndef trans_file_h
#define trans_file_h

#ifdef TRANS_FILE_EXPORTS
#define TRANS_FILE_API __declspec(dllexport)
#else
#define TRANS_FILE_API __declspec(dllimport)
#endif

struct tf_common_event {
  int id;
  int tag;
  tf_common_event(int ID, int Tag) : id(ID), tag(Tag) {}
};

typedef void (*HandlerFunc)(const tf_common_event& Event);

#ifdef __cplusplus
extern "C" {
#endif

  TRANS_FILE_API void __stdcall tf_init();

  TRANS_FILE_API void __stdcall tf_destroy();

  // while tf_rcvAndDisp do {...}
  TRANS_FILE_API bool __stdcall tf_rcvAndDisp();

  // Set callback function 
  TRANS_FILE_API void tf_set_handler(HandlerFunc handler);
  

  // Send file, return SessionID
  TRANS_FILE_API bool __stdcall tf_send_file(const char* filePath, size_t sizeFilePath);

  // Prepare for receive file on destination
  TRANS_FILE_API void __stdcall tf_prepare_receive_file(int SessionID);

  // Receive file as file_name
  TRANS_FILE_API bool __stdcall tf_receive_file(int SessionID, const char* filePath, size_t sizeFilePath);

  TRANS_FILE_API bool __stdcall tf_send_file_cancel(int SessionId);

  TRANS_FILE_API bool __stdcall tf_receive_file_cancel(int SessionId);
  
  //set host and port tf_server
  TRANS_FILE_API void tf_set_params(const char* Host, size_t len, unsigned short Port);

#ifdef __cplusplus
}
#endif











#define TF_TAG_ERROR_EVENT 33

struct tf_error_event : public tf_common_event {
  int error_code;
  char what[256];
  tf_error_event(int ID, int Error_Code, const char* What=0);
};

#define TF_TAG_ERROR_OPEN_FILE 10001
#define TF_TAG_ERROR_NOT_CONNECTED 10002


#define TF_TAG_UPLOAD_INIT_EVENT 34

struct tf_upload_init_event : public tf_common_event {
  char file_name[255];
  int file_size;
  unsigned short fn_len;
  tf_upload_init_event(int ID, const char* File_Name, size_t FNlen, int File_Size);
};


#define TF_TAG_DOWNLOAD_INIT_EVENT 35

struct tf_download_init_event : public tf_common_event {
  char file_name[255];
  unsigned short fn_len;
  int file_size;
  tf_download_init_event(int ID, const char* FileName, size_t FNlen, size_t FileSize);
};


#define TF_TAG_UPLOAD_START_EVENT 40

struct tf_upload_start_event : public tf_common_event {
  tf_upload_start_event(int ID) 
    : tf_common_event(ID, TF_TAG_UPLOAD_START_EVENT) {
  };
};


#define TF_TAG_UPLOAD_PENDING_EVENT 41

struct tf_upload_pending_event : public tf_common_event {
  unsigned int offset;
  tf_upload_pending_event(int ID, int Offset) 
    : tf_common_event(ID, TF_TAG_UPLOAD_PENDING_EVENT), offset(Offset) {
  };
};


#define TF_TAG_UPLOAD_COMPLETE_EVENT 42

struct tf_upload_complete_event : public tf_common_event {
  tf_upload_complete_event(int ID) 
    : tf_common_event(ID, TF_TAG_UPLOAD_COMPLETE_EVENT) {
  };
};


#define TF_TAG_DOWNLOAD_START_EVENT 50

struct tf_download_start_event : public tf_common_event {
  tf_download_start_event(int ID) 
    : tf_common_event(ID, TF_TAG_DOWNLOAD_START_EVENT) {
  };
};


#define TF_TAG_DOWNLOAD_PENDING_EVENT 51

struct tf_download_pending_event : public tf_common_event {
  unsigned int offset;
  tf_download_pending_event(int ID, unsigned int Offset) 
    : tf_common_event(ID, TF_TAG_DOWNLOAD_PENDING_EVENT), offset(Offset) {
  };
};


#define TF_TAG_DOWNLOAD_COMPLETE_EVENT 52

struct tf_download_complete_event : public tf_common_event {
  tf_download_complete_event(int ID) 
    : tf_common_event(ID, TF_TAG_DOWNLOAD_COMPLETE_EVENT) {
  };
};

#define TF_TAG_DISCONNECT_EVENT 100

struct tf_disconnect_event : public tf_common_event {
  tf_disconnect_event(int ID) 
    : tf_common_event(ID, TF_TAG_DISCONNECT_EVENT) {
  };
};

#endif