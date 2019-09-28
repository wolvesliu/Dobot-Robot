/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"





//EventsFunctionList
void OnButtonClicked_Clear(WM_MESSAGE * pMsg);
void OnButtonClicked_Temination(WM_MESSAGE * pMsg);
void OnButtonClicked_Stat(WM_MESSAGE * pMsg);
void OnButtonClicked_Reset(WM_MESSAGE * pMsg);
void OnButtonClicked_Back(WM_MESSAGE * pMsg);


void OnButtonReleased_Line(WM_MESSAGE * pMsg);
void OnButtonReleased_Arc(WM_MESSAGE * pMsg);
void OnButtonReleased_Circle(WM_MESSAGE * pMsg);


void OnButtonMovedOut_BigUp(WM_MESSAGE * pMsg);
void OnButtonMovedOut_BigDown(WM_MESSAGE * pMsg);
void OnButtonMovedOut_SmallUp(WM_MESSAGE * pMsg);
void OnButtonMovedOut_SmallDown(WM_MESSAGE * pMsg);
void OnButtonMovedOut_BaseLeft(WM_MESSAGE * pMsg);
void OnButtonMovedOut_BaseRight(WM_MESSAGE * pMsg);




//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  480,800,FRAMEWIN_CF_MOVEABLE,0},
    { TEXT_CreateIndirect,      "Intelligente Robot System",GUI_ID_TEXT0,            -1, 34, 478,82, 0,0},
    { TEXT_CreateIndirect,      "X axis: normal state",GUI_ID_TEXT2,            13, 178,181,32, 0,0},
    { TEXT_CreateIndirect,      "Z axis: normal state",GUI_ID_TEXT4,            13, 241,181,27, 0,0},
    { TEXT_CreateIndirect,      "Y axis: normal state",GUI_ID_TEXT3,            13, 210,181,32, 0,0},
    { TEXT_CreateIndirect,      "The state of robitic arm",GUI_ID_TEXT1,            13, 150,204,32, 0,0},
    { BUTTON_CreateIndirect,    "Clear abnormal",    GUI_ID_BUTTON1,          271,213,186,52, 0,0},
    { BUTTON_CreateIndirect,    "Temination",        GUI_ID_BUTTON5,          322,705,141,54, 0,0},
    { BUTTON_CreateIndirect,    "Stat",              GUI_ID_BUTTON4,          219,705,91, 54, 0,0},
    { BUTTON_CreateIndirect,    "Reset",             GUI_ID_BUTTON3,          105,705,89, 54, 0,0},
    { BUTTON_CreateIndirect,    "Back",              GUI_ID_BUTTON2,          7,  705,82, 54, 0,0},
    { BUTTON_CreateIndirect,    "Line",              GUI_ID_BUTTON6,          22, 584,108,52, 0,0},
    { BUTTON_CreateIndirect,    "Arc",               GUI_ID_BUTTON7,          151,584,115,52, 0,0},
    { BUTTON_CreateIndirect,    "Circle",            GUI_ID_BUTTON8,          293,584,117,51, 0,0},
    { BUTTON_CreateIndirect,    "Up",                GUI_ID_BUTTON9,          39, 412,92, 41, 0,0},
    { BUTTON_CreateIndirect,    "Down",              GUI_ID_MAXIMIZE,         39, 474,92, 43, 0,0},
    { BUTTON_CreateIndirect,    "Up",                GUI_ID_YES,              186,411,104,41, 0,0},
    { BUTTON_CreateIndirect,    "Down",              GUI_ID_NO,               185,474,105,43, 0,0},
    { BUTTON_CreateIndirect,    "Left",              GUI_ID_CLOSE,            351,411,95, 42, 0,0},
    { BUTTON_CreateIndirect,    "Right",             GUI_ID_HELP,             351,474,95, 43, 0,0},
    { TEXT_CreateIndirect,      "Robotic Arm Joints",GUI_ID_TEXT6,            11, 354,185,22, 0,0},
    { TEXT_CreateIndirect,      "Big arm",           GUI_ID_TEXT7,            48, 380,73, 28, 0,0},
    { TEXT_CreateIndirect,      "Small arm",         GUI_ID_TEXT8,            198,384,82, 23, 0,0},
    { TEXT_CreateIndirect,      "Base",              GUI_ID_TEXT9,            361,382,85, 26, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_2(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(8,146,8,272);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(465,146,465,272);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(9,146,464,146);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(9,272,464,272);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(8,349,460,349);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(10,533,459,533);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(460,349,460,532);
    GUI_SetColor(0x0000ff);
    GUI_DrawLine(9,350,9,532);

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_2(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0xffff80);
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT0),0x80ffff);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_Font24_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xffff80);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT2),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT2),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT4
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xffff80);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT4),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xffff80);
    TEXT_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_TEXT3),0xff0000);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT3),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT1),0xffff80);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font16_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0x8080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),BUTTON_CI_UNPRESSED,0xffc0ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),BUTTON_CI_UNPRESSED,0xffc0ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),BUTTON_CI_UNPRESSED,0xffc0ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_CI_UNPRESSED,0xffc0ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),BUTTON_CI_UNPRESSED,0xc0e0ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),BUTTON_CI_UNPRESSED,0xc0ffff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),BUTTON_CI_UNPRESSED,0xc0ffff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),&GUI_Font24_ASCII);
    //
    //GUI_ID_BUTTON9
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),BUTTON_CI_UNPRESSED,0x8080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),&GUI_Font24_ASCII);
    //
    //GUI_ID_MAXIMIZE
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_MAXIMIZE),BUTTON_CI_UNPRESSED,0x8080ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_MAXIMIZE),&GUI_Font24_ASCII);
    //
    //GUI_ID_YES
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_YES),BUTTON_CI_UNPRESSED,0x80ff80);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_YES),&GUI_Font24_ASCII);
    //
    //GUI_ID_NO
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_NO),BUTTON_CI_UNPRESSED,0x80ff80);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_NO),&GUI_Font24_ASCII);
    //
    //GUI_ID_CLOSE
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_CLOSE),BUTTON_CI_UNPRESSED,0xff8080);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_CLOSE),&GUI_Font24_ASCII);
    //
    //GUI_ID_HELP
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_HELP),BUTTON_CI_UNPRESSED,0xff8080);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_HELP),&GUI_Font24_ASCII);
    //
    //GUI_ID_TEXT6
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT6),0xffff80);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT6),&GUI_Font16B_1);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT6),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT7
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT7),0xffff80);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT7),&GUI_Font16B_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT7),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT8
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT8),0xffff80);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT8),&GUI_Font16B_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT8),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT9
    //
    TEXT_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_TEXT9),0xffff80);
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT9),&GUI_Font16B_ASCII);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT9),GUI_TA_VCENTER|GUI_TA_CENTER);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_2(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_2(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Clear(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON5:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Temination(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON4:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Stat(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Reset(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Back(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON6:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonReleased_Line(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON7:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonReleased_Arc(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON8:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonReleased_Circle(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON9:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_BigUp(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_MAXIMIZE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_BigDown(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_YES:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_SmallUp(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_NO:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_SmallDown(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_CLOSE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_BaseLeft(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_HELP:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_MOVED_OUT:
                            OnButtonMovedOut_BaseRight(pMsg);
                            break;
                    }
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       Task_2
*
**********************************************************************
*/
void Task_2(void) 
{ 
//    GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
//    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

