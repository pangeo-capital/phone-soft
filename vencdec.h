#ifndef video_enc_dec_h
#define video_enc_dec_h

#ifdef VENCDEC_EXPORTS
#define VENCDEC_API __declspec(dllexport)
#else
#define VENCDEC_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*RTPCALLBACKPROCPTR)( int encoderId, unsigned char *data, int size, int mb_nb );

/*
	������������� ����������

	���������� 0 ��� ������� �������������
*/
	VENCDEC_API int vencdec_init();

/*
	����� ����������
*/
	VENCDEC_API void vencdec_destroy();

/*
	�������� scaler'�

	���������� ������������� ������� ��� �������� ������, ��� ������ ���������� ������������� ��������
*/

	VENCDEC_API int vencdec_create_scaler( );


/*
	������� scaler

	[in] decoderId	- ������������� �������, ���������� ����� vencdec_create_scaler
*/
	VENCDEC_API void vencdec_destroy_scaler( int scalerId );

/*
	� ��� �������� � ������ ��� � RGB24, � �� ���� ������ ���� � YUV420P, 
	������� ����� ������� vencdec_encode ���� ������� vencdec_rgb24_to_yuv420p 

	����� ������ ������� ���������� ���������������

	[in] srcWidth	- �������� ������
	[in] srcHeight	- �������� ������
	[in] idata		- ����� � ������
	[in] idata_len	- ������ ������ idata
	[in] dstWidth	- �������� ������
	[in] dstHeight	- �������� ������
	[in] odata	- �����, � ������� ����� �������� ����� �������� (���������� �����������)
	[in] odata_len	- ������ ������ odata

	���������� ���������� ����, ���������� � ����� odata
*/
	VENCDEC_API int vencdec_rgb24_to_yuv420p( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_bgr24_to_yuv420p( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

/*
	�� ���� �������� �������� � YUV420, ������� ���� ���� �������, 
	����� ������������ �� h263 � ����� ������������� � RGB24

	����� ������ ������� ���������� ���������������

	[in] srcWidth	- �������� ������
	[in] srcHeight	- �������� ������
	[in] idata		- ����� � ������
	[in] idata_len	- ������ ������ idata
	[in] dstWidth	- �������� ������
	[in] dstHeight	- �������� ������
	[in] odata	- �����, � ������� ����� �������� ����� �������� (���������� �����������)
	[in] odata_len	- ������ ������ odata

	���������� ���������� ����, ���������� � ����� odata
*/
	VENCDEC_API int vencdec_yuv420p_to_rgb24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_yuv420p_to_bgr24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_rgb24_to_rgb24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_bgr24_to_bgr24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

/*
	[in] dstWidth	- ������
	[in] dstHeight	- ������

	���������� ���-�� ���� ����������� ��� ���������� �������� RGB24 dstWidth X dstHeight
*/
	VENCDEC_API int vencdec_get_rgb24_buff_size( int dstWidth, int dstHeight );

/*
	[in] dstWidth	- ������
	[in] dstHeight	- ������

	���������� ���-�� ���� ����������� ��� ���������� �������� BGR24 dstWidth X dstHeight
*/
	VENCDEC_API int vencdec_get_bgr24_buff_size( int dstWidth, int dstHeight );

/*
	[in] dstWidth	- ������
	[in] dstHeight	- ������

	���������� ���-�� ���� ����������� ��� ���������� �������� YUV420P dstWidth X dstHeight
*/

	VENCDEC_API int vencdec_get_yuv420p_buff_size( int dstWidth, int dstHeight );
	

/*
	�������� ����������� h263

	[in] width	- ������ ���������� ��������
	[in] height	- ������ ���������� ��������
	[in] fps	- ������ � �������

	���������� ������������� ����������� ��� �������� ������, ��� ������ ���������� ������������� ��������
*/
	VENCDEC_API int vencdec_create_encoder( int width, int height, int fps, int max_payload_size );

/*
	������� ����������

	[in] encoderId	- ������������� �����������, ���������� ����� vencdec_create_encoder
*/
	VENCDEC_API void vencdec_destroy_encoder( int encoderId );

	VENCDEC_API void vencdec_set_encoder_rtp_handler( RTPCALLBACKPROCPTR rtpCallBackPtr );	 

/*
	����������� � H263

	!!!!!!!!!!! �������� ��������� � YUV420P

	[in] encoderId	- ������������� �����������, ���������� ����� vencdec_create_encoder
	[in] idata		- ����� � ������
	[in] idata_len	- ������ ������ idata
	[in] odata	- �����, � ������� ����� �������� ����� �������� (���������� �����������)
	[in] odata_len	- ������ ������ odata

	���������� ���������� ����, ���������� � ����� odata
*/
	VENCDEC_API int vencdec_encode( int encoderId, unsigned char* idata, int idata_len, unsigned char* odata, int odata_len);

/*
	�������� ������������� h263

	���������� ������������� ������������� ��� �������� ������, ��� ������ ���������� ������������� ��������
*/

	VENCDEC_API int vencdec_create_decoder( );

/*
	������� ������������

	[in] decoderId	- ������������� �������������, ���������� ����� vencdec_create_decoder
*/
	VENCDEC_API void vencdec_destroy_decoder( int decoderId );

/*
	�������������� �� H263

	[in] decoderId	- ������������� �������������, ���������� ����� vencdec_create_decoder
	[in] idata		- ����� � ������
	[in] idata_len	- ������ ������ idata
	[in] odata		- �����, � ������� ����� �������� ����� �������� (���������� �����������)
	[in] odata_len	- ������ ������ odata
	[out] width		- ������ ���������� ��������
	[out] height	- ������ ���������� ��������

	���������� ���������� ����, ���������� � ����� odata
*/
	VENCDEC_API int vencdec_decode( int decoderId, unsigned char* idata, int idata_len, unsigned char* odata, int odata_len, int* width, int* height );


#ifdef __cplusplus
}
#endif

#endif