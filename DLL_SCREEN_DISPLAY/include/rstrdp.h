#ifndef rst_rdp_h
#define rst_rdp_h

#ifdef RSTRDP_EXPORTS
#define RSTRDP_API __declspec(dllexport)
#else
#define RSTRDP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	RSTRDP_API void rdp_init();
	RSTRDP_API void rdp_destroy();
	RSTRDP_API void rdp_start_sharing( const char* invitation_data, int inv_length, int& length_out );
	RSTRDP_API void rdp_stop_sharing();
	RSTRDP_API void rdp_connect(const char* invitation_data, int length_in );
	RSTRDP_API void rdp_disconnect();

#ifdef __cplusplus
}
#endif

#endif