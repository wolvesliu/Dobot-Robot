#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

extern void Task_1(void);

/************************************************************************************************/
/*
 *
 *	函数功能：清除异常 
 *
 */
void OnButtonClicked_Clear(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON1
{
}	


/*
 *
 *	函数功能：终止机械臂运动
 *
 */
void OnButtonClicked_Temination(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON5
{
}	


/*
 *
 *	函数功能：启动机械臂
 *
 */
void OnButtonClicked_Stat(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON4
{
}	


/*
 *
 *	函数功能：机械臂复位
 *
 */
void OnButtonClicked_Reset(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON3
{
}	


/*
 *
 *	函数功能：返回上一页面
 *
 */
void OnButtonClicked_Back(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON2
{
	Task_1();
}	


/************************************************************************************************/
/*
 *
 *	函数功能：画直线
 *
 */
void OnButtonReleased_Line(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON6
{
}	


/*
 *
 *	函数功能：画圆弧
 *
 */
void OnButtonReleased_Arc(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON7
{
}	


/*
 *
 *	函数功能：画圆
 *
 */
void OnButtonReleased_Circle(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON8
{
}	



/**************************************************************************************************/
/*
 *
 *	函数功能：大臂向上运动
 *
 */
void OnButtonMovedOut_BigUp(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON9
{
}	


/*
 *
 *	函数功能：大臂向下运动
 *
 */
void OnButtonMovedOut_BigDown(WM_MESSAGE * pMsg)					// GUI_ID_MAXIMIZE
{
}	


/*
 *
 *	函数功能：小臂向上运动
 *
 */
void OnButtonMovedOut_SmallUp(WM_MESSAGE * pMsg)					// GUI_ID_YES
{
}	


/*
 *
 *	函数功能：小臂向下运动
 *
 */
void OnButtonMovedOut_SmallDown(WM_MESSAGE * pMsg)					// GUI_ID_NO
{
}	


/*
 *
 *	函数功能：底座向左转
 *
 */
void OnButtonMovedOut_BaseLeft(WM_MESSAGE * pMsg)					// GUI_ID_CLOSE
{
}	


/*
 *
 *	函数功能：底座向右转
 *
 */
void OnButtonMovedOut_BaseRight(WM_MESSAGE * pMsg)					// GUI_ID_HELP
{
}	





