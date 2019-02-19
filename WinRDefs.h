#ifndef WINR_Defs_H
#define WINR_Defs_H
#ifndef WIN32
 #define WIN32 1
#endif 
#define NOSSL

   //  #define DEBUG__SIP__CLIENT    //MUST BE UNDEF IN RELEASED VARIANT !!!!!!!!!!
   //  #define DEBUG__START__CLIENT  //MUST BE UNDEF IN RELEASED VARIANT !!!!!!!!!!

#define SIP_Video
#define RTP_exsCreateUDPSocket_ADDR_ANY
#define SIP_LogSendPacket
#define SIP_ResendQueue_Log
#define SIP_Uac_In_QUEUE_Log
#define SIP_Uac_SENT_QUEUE_Log
#define SIP_UA_RESEND_LIST_Log
#define SIP_Erase_Resend_Req_Log
#define SIP_Thread_Destruction_Log
#define SIP_Thread_Resend_Proc_Log
#define SIP_Proc_SRST_MSG_Log
#define RTP_Print_All_Connections_On_Connect
#define RTP_Print_Session_On_Create
#define SIP_PrintAll_Uac_CallID
#define SIP_PrintAll_Uas_CallID
#define SubscDB_LogSendPacket
#define SubscDB_LogRecvPacket
#define SubscDB_LogParsedPacket
#define Enterprise_Edition
#define Contact_HTTP_FileTransfer
#define USE_WIN_DSP_CAPTURE_CAPABILITIES   // AudioEchoCompensation, Noise Suppr, AutomaticGainControl
#define Dsp_VAD                            // Voice Activity Detection

// #define Wait_For_First_Mic_Packet

 //     #define Call_Btn_On_The_Middle_Of_The_Field

//     #define StructuralContactsImport

//#define NET_STATE_DISPLAY_DEPEND_OF_COS

//    #define VIDEO_CAP_WITH_WINDOWS_FUNC

#define SCREEN_Sharing_over_rem_server

#define Place_OnHold_All_ActiveCalls__OnActivateNewCall

#define Client_Test_Block


        //   #define Log_Audio_Conference_Mixed_Packet
        //      #define Log_Capture_DSP

        //   #define Client_Test_Sound

                         //#define Full_Fourie_Transform
                         //#define Sound_Freq_Zero  //подсчет пост составл€ющей в звукоывых отсчетах
//#define SIP_Transport_TLS

//#define NO_BRAND
#define INTRN_TCP

       //#define Hide_Video_Menu
#define Hide_Transport_Menu

#define Receiving_Wave_Format_PCM
//#define Send_Msg_Text__html


//#define RTP_whdr_Trace


#define RTP_ProFile_Trace
// #define RTP_Print_EventLogQueue

#define BaseExchBlock_Create
//#define TOutPutDtmfBlock_Create
//#define RTP_LogSendPacket

//#define PCS_Trace
//#define RTP_Tunnel_LogSendBufPacket
#define RTP_Tunnel_2833_LogSendBufPacket

#define RTP_LogSendBufPacket

//#define Send_IM_reference_like_HTML_ref
//#define Receive_IM_reference_like_HTML_ref   - не закончено !


                                     /*
                                     #define SCREEN_Sharing_frame

                                     #define ScreenSharing_Loc_OUT_Send_Log
                                     #define ScreenSharing_Rem_OUT_Send_Log

                                     #define ScreenSharing_Loc_IN_Send_Log
                                     #define ScreenSharing_Rem_IN_Send_Log

                                     #define ScreenSharing_Loc_OUT_Rcv_Log
                                     #define ScreenSharing_Rem_OUT_Rcv_Log

                                     #define ScreenSharing_Loc_IN_Rcv_Log
                                     #define ScreenSharing_Rem_IN_Rcv_Log
                                     */

  //     #define Automatic_Out_Calls   // Ѕлок исход€щих вызовов

#define Tcp_Sock_Log

#define IMG_N_Style

//#define TRACE_ALLOC_MEM

#endif