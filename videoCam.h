#ifndef video_cam_h
#define video_cam_h

#ifdef VIDEOCAM_EXPORTS
#define VIDEOCAM_API __declspec(dllexport)
#else
#define VIDEOCAM_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	VIDEOCAM_API void  vcam_init();

	VIDEOCAM_API void  vcam_destroy();

	VIDEOCAM_API int  vcam_get_device_count();

	VIDEOCAM_API bool  vcam_setup_device( int devId, int width, int height );

	VIDEOCAM_API void  vcam_set_ideal_frame_rate( int devId, int frame_rate );

	VIDEOCAM_API void  vcam_stop_device( int devId );

	VIDEOCAM_API bool  vcam_is_frame_new( int devId );

	VIDEOCAM_API bool  vcam_get_pixels( int devId, unsigned char* buff, bool flip_red_blue, bool flip_image );

	VIDEOCAM_API char*  vcam_get_name( int devId );

	VIDEOCAM_API int  vcam_get_width( int devId );

	VIDEOCAM_API int  vcam_get_height( int devId );
	
	VIDEOCAM_API int  vcam_get_size( int devId );

#ifdef __cplusplus
}
#endif

#endif