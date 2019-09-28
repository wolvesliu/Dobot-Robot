#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

extern void Task_2(void);

/*
 *
 *	函数功能：进入下一界面，进入系统 
 *
 */
void OnButtonClicked_EnterSys(WM_MESSAGE * pMsg)
{
	Task_2();
}

