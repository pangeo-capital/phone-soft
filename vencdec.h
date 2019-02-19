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
	Инициализация библиотеки

	Возвращает 0 при удачной инициализации
*/
	VENCDEC_API int vencdec_init();

/*
	сброс библиотеки
*/
	VENCDEC_API void vencdec_destroy();

/*
	Создание scaler'а

	Возвращает идентификатор объекта при успешном вызове, при ошибке возвращает отрицательное значение
*/

	VENCDEC_API int vencdec_create_scaler( );


/*
	Удаляет scaler

	[in] decoderId	- Идентификатор объекта, полученный через vencdec_create_scaler
*/
	VENCDEC_API void vencdec_destroy_scaler( int scalerId );

/*
	У нас картинка с камеры идёт в RGB24, а по сети должна идти в YUV420P, 
	поэтому перед вызовом vencdec_encode надо вызвать vencdec_rgb24_to_yuv420p 

	Также данная функция производит масштабирование

	[in] srcWidth	- Исходная ширина
	[in] srcHeight	- Исходная высота
	[in] idata		- Буфер с кадром
	[in] idata_len	- Размер буфера idata
	[in] dstWidth	- Конечная ширина
	[in] dstHeight	- Конечная высота
	[in] odata	- Буфер, в который будет помещена новая картинка (выделяется вызывателем)
	[in] odata_len	- Размер буфера odata

	Возвращает количество байт, помещённых в буфер odata
*/
	VENCDEC_API int vencdec_rgb24_to_yuv420p( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_bgr24_to_yuv420p( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

/*
	Из сети картинка приходит в YUV420, поэтому если есть желание, 
	после разкодировки из h263 её можно преобразовать в RGB24

	Также данная функция производит масштабирование

	[in] srcWidth	- Исходная ширина
	[in] srcHeight	- Исходная высота
	[in] idata		- Буфер с кадром
	[in] idata_len	- Размер буфера idata
	[in] dstWidth	- Конечная ширина
	[in] dstHeight	- Конечная высота
	[in] odata	- Буфер, в который будет помещена новая картинка (выделяется вызывателем)
	[in] odata_len	- Размер буфера odata

	Возвращает количество байт, помещённых в буфер odata
*/
	VENCDEC_API int vencdec_yuv420p_to_rgb24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_yuv420p_to_bgr24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_rgb24_to_rgb24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

	VENCDEC_API int vencdec_bgr24_to_bgr24( int scalerId, int srcWidth, int srcHeight, unsigned char* idata, int idata_len, int dstWidth, int dstHeight, unsigned char* odata, int odata_len );

/*
	[in] dstWidth	- Ширина
	[in] dstHeight	- Высота

	Возвращает кол-во байт необходимое для размещения картинки RGB24 dstWidth X dstHeight
*/
	VENCDEC_API int vencdec_get_rgb24_buff_size( int dstWidth, int dstHeight );

/*
	[in] dstWidth	- Ширина
	[in] dstHeight	- Высота

	Возвращает кол-во байт необходимое для размещения картинки BGR24 dstWidth X dstHeight
*/
	VENCDEC_API int vencdec_get_bgr24_buff_size( int dstWidth, int dstHeight );

/*
	[in] dstWidth	- Ширина
	[in] dstHeight	- Высота

	Возвращает кол-во байт необходимое для размещения картинки YUV420P dstWidth X dstHeight
*/

	VENCDEC_API int vencdec_get_yuv420p_buff_size( int dstWidth, int dstHeight );
	

/*
	Создание кодировщика h263

	[in] width	- Ширина кодируемой картинки
	[in] height	- Высота кодируемой картинки
	[in] fps	- кадров в секунду

	Возвращает идентификатор кодировщика при успешном вызове, при ошибке возвращает отрицательное значение
*/
	VENCDEC_API int vencdec_create_encoder( int width, int height, int fps, int max_payload_size );

/*
	Удаляет кодировщик

	[in] encoderId	- Идентификатор кодировщика, полученный через vencdec_create_encoder
*/
	VENCDEC_API void vencdec_destroy_encoder( int encoderId );

	VENCDEC_API void vencdec_set_encoder_rtp_handler( RTPCALLBACKPROCPTR rtpCallBackPtr );	 

/*
	Кодирование в H263

	!!!!!!!!!!! Картинка ожидается в YUV420P

	[in] encoderId	- Идентификатор кодировщика, полученный через vencdec_create_encoder
	[in] idata		- Буфер с кадром
	[in] idata_len	- Размер буфера idata
	[in] odata	- Буфер, в который будет помещена новая картинка (выделяется вызывателем)
	[in] odata_len	- Размер буфера odata

	Возвращает количество байт, помещённых в буфер odata
*/
	VENCDEC_API int vencdec_encode( int encoderId, unsigned char* idata, int idata_len, unsigned char* odata, int odata_len);

/*
	Создание декодировщика h263

	Возвращает идентификатор декодировщика при успешном вызове, при ошибке возвращает отрицательное значение
*/

	VENCDEC_API int vencdec_create_decoder( );

/*
	Удаляет декодировщик

	[in] decoderId	- Идентификатор декодировщика, полученный через vencdec_create_decoder
*/
	VENCDEC_API void vencdec_destroy_decoder( int decoderId );

/*
	Разкодирование из H263

	[in] decoderId	- Идентификатор декодировщика, полученный через vencdec_create_decoder
	[in] idata		- Буфер с кадром
	[in] idata_len	- Размер буфера idata
	[in] odata		- Буфер, в который будет помещена новая картинка (выделяется вызывателем)
	[in] odata_len	- Размер буфера odata
	[out] width		- Ширина полученной картинки
	[out] height	- Высота полученной картинки

	Возвращает количество байт, помещённых в буфер odata
*/
	VENCDEC_API int vencdec_decode( int decoderId, unsigned char* idata, int idata_len, unsigned char* odata, int odata_len, int* width, int* height );


#ifdef __cplusplus
}
#endif

#endif