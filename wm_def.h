#ifndef SIP_CLIENT_WM_DEF_H
#define SIP_CLIENT_WM_DEF_H

//------------------------------------------------------------------------------
#define SIP_UA_MSG         (WM_APP + 1) //Window Msg (WM) From User Agent (Uac or Uas)
#define SOUND_MSG          (WM_APP + 2) //Window Msg (WM) From TWaveOutputThread
#define CALL_MSG           (WM_APP + 3) //Window Msg (WM) From Form1 (CallIN - Inf Window about incoming call)
#define VIDEOOUT_MSG       (WM_APP + 4) //Window Msg (WM) From Form4 (Video)
#define FILE_TRANSFER_MSG  (WM_APP + 5) //Window Msg (WM) From File_Transfer_Thread -> MainForm
#define CONTROL_MSG        (WM_APP + 6) //For Close(Open) Controls (Panels and so on)
#define REFER_BTN_MSG      (WM_APP + 7) //For ReferWin change btn state
#define REMOTE_VIDEO_MSG   (WM_APP + 8) //For TForm3 window (remote video)
#define CONFERENCE_MSG     (WM_APP + 9)  //For TConference window (msgs about conference participants)
#define CONFERENCE_PLAIN_MSG (WM_APP + 10) //For TConference window without additional buf

//------------------------------------------------------------------------------
typedef enum{
WM_APP_MSG_WPARAM__UAC,
WM_APP_MSG_WPARAM__UAS,
WM_APP_MSG_WPARAM__CALL_IN,
WM_APP_MSG_WPARAM__CALL_OUT,
WM_APP_MSG_WPARAM__VIDEOOUT,
WM_APP_MSG_WPARAM__FILE_TRANS_INIT_MSG,
WM_APP_MSG_WPARAM__FILE_TRANS_START_MSG,
WM_APP_MSG_WPARAM__FILE_TRANS_END,
WM_APP_MSG_WPARAM__FILE_RECV_END,
WM_APP_MSG_WPARAM__FILE_PENDING_MSG,
WM_APP_MSG_WPARAM__CLOSE_COMMENT_PANEL,
WM_APP_MSG_WPARAM__DRAWGRID_ROW_COUNT,
WM_APP_MSG_WPARAM__DRAWGRID_FIND_ROW_COUNT,
WM_APP_MSG_WPARAM__DRAWGRID_FIND_REPAINT,
WM_APP_MSG_WPARAM__LAST_CALLS__DRAWGRID_ROW_COUNT,
WM_APP_MSG_WPARAM__IM__DRAWGRID_RESIZE_ON_CHANGE_CALL_COUNT,
WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT,
WM_APP_MSG_WPARAM__IM__DRAWGRID_ROW_COUNT_ON_SEND_TEXT_MSG,
WM_APP_MSG_WPARAM__IM_READBLOCK__DRAWGRID_ROW_COUNT,
WM_APP_MSG_WPARAM__IM_READBLOCK__ONTOP_DRAWGRID_ROW_COUNT,
WM_APP_MSG_WPARAM__DBI_DATA,
WM_APP_MSG_WPARAM__SCREEN_SHARING_OUT_DATA,
WM_APP_MSG_WPARAM__SCREEN_SHARING_IN_DATA,
WM_APP_MSG_WPARAM__CLOSE_DB_CHANNEL,
WM_APP_MSG_WPARAM__INIT_REG_PROC,
WM_APP_MSG_WPARAM__TCP_CONNECTION_DROPPED,
WM_APP_MSG_WPARAM__SELECT_FIRST_MISSED_CALL,
WM_APP_MSG_WPARAM__CLOSE_WINDOW,
WM_APP_MSG_WPARAM__IM_REPAINT,
WM_APP_MSG_WPARAM__NDEF,
}WM_APP_MSG_WPARAM;
//------------------------------------------------------------------------------
typedef enum{
WM_APP_MSG_LPARAM__NOPARAM,
WM_APP_MSG_LPARAM__READLIST,
WM_APP_MSG_LPARAM__READLIST_PPH,
WM_APP_MSG_LPARAM__REGISTER_FAILED,
WM_APP_MSG_LPARAM__CONTACT_LIST_REFRESH,
WM_APP_MSG_LPARAM__FINAL_REG_END,
WM_APP_MSG_LPARAM__END_OF_PLAY_REORDER,
WM_APP_MSG_LPARAM__END_OF_PLAY_BUSY,
}WM_APP_MSG_LPARAM;
//------------------------------------------------------------------------------
#endif 
