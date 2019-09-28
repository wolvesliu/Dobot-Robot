#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ILI93xx.h"
#include "key.h"  
#include "timer.h"
#include "sram.h"   
#include "malloc.h" 
#include "touch.h" 
#include "GUIDemo.h"
#include "GUI.h"

#include "interpolation.h"
#include "decode.h"

extern void Task_1(void);
extern void Task_2(void);

int main(void)
{        
	extern GCode_Msg* pGCode_Msg;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  			//初始化延时函数
	uart_init(115200);			//初始化串口波特率为115200
	LED_Init();							//初始化LED
 	TFTLCD_Init();					//LCD初始化 
	TP_Init();							//初始化触摸屏
 	KEY_Init();							//按键初始化 
 	FSMC_SRAM_Init();				//初始化外部SRAM  
	TIM3_Int_Init(999,83); 	//1KHZ 定时器3设置为1ms

	my_mem_init(SRAMIN);		//初始化内部内存池
	my_mem_init(SRAMEX);		//初始化外部内存池
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	TIM4_Int_Init(999,839); //触摸屏扫描速度,100HZ.
	//TIM4_Int_Init(100-1,8400-1);//10ms

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);//开启CRC时钟
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();									//emWin初始化
	
	pGCode_Msg=(GCode_Msg*)malloc(sizeof(GCode_Msg));//动态内存申请
			 
	Task_1();	
	Task_2();
	
	  while(1)
	{
		GUI_Exec();//功能运行函数，比如更新窗口
	}		
}


