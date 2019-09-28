#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "led.h"
#include "decode.h"
#include "interpolation.h"
#include "usart.h"
#include "delay.h"


extern GCode_Msg* pGCode_Msg;
extern double x,y,z,L1,L2,L3; 
extern int i;


char* pcode;	//取一行的指针

extern void Task_1(void);





/************************************************************************************************/
/*
 *
 *	函数功能：清除异常 
 *
 */
void OnButtonClicked_Clear(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON1
{
	Reset_Dobot();					//	复位函数调用
}	


/*
 *
 *	函数功能：终止机械臂运动
 *
 */
void OnButtonClicked_Temination(WM_MESSAGE * pMsg)		// GUI_ID_BUTTON5
{
	LED1 = 0;
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
	LED0 = 0;
	Reset_Dobot();					//复位函数调用
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
	 int word = 1;
	 
	 while(word <= 6)
	 {
		 switch (word)
		 {
			 case 1:pcode = "G01X120Y0Z93F800";break;
			 case 2:pcode = "G01X120Y20Z93F800";break;
			 case 3:pcode = "G01X140Y20Z93F800";break;
			 case 4:pcode = "G01X140Y0Z93F800";break;
			 case 5:pcode = "G01X120Y0Z93F800";break;
			 case 6:pcode = "G01X120Y0Z120F800";break;			 
		 }
		printf("获取代码:%s\r\n",pcode);
	 
	 //译码
		printf("译码\r\n");
		decode(pcode);//译码函数
		printf("pGCode_Msg->G_instruct = %u\r\n",pGCode_Msg->G_instruct);
		
		GetArcO1(pGCode_Msg);//调用求圆心函数
		printf("pGCode_Msg->O_X = %f\r\n",pGCode_Msg->O_X);
		printf("pGCode_Msg->O_Y = %f\r\n",pGCode_Msg->O_Y);

		 x = pGCode_Msg->coor_value[0];
		 y = pGCode_Msg->coor_value[1];
		 z = pGCode_Msg->coor_value[2];
		 printf("x = %f\r\n",x);
		 
	 /************G01	直线插补************/
		if(pGCode_Msg->G_instruct == 0x01)	
		{
				Inverse_Solution();				//反解函数调用
				Line_Interpolation();			//直线插补函数调用
			 
				for(i=0; i < 3; i++) 
				{
					pGCode_Msg->coor_currentValue[i] = pGCode_Msg->coor_value[i];  //保存当前坐标
					printf("pGCode_Msg->coor_currentValue[%d] = %d\r\n",i, pGCode_Msg->coor_currentValue[i]);									
				}

		}
	 
		/*********G02	顺圆弧插补	***********/
		if(pGCode_Msg->G_instruct == 0x02)	
		{
			//先调用直线插补到达起点
			Inverse_Solution();				//反解函数调用
			Line_Interpolation();			//直线插补函数调用
			
			//然后再顺圆弧插补
			Arc_Interpolation(pGCode_Msg);//顺圆弧插补
		
		}
		
		/*********G03	逆圆弧插补	***********/	
		if(pGCode_Msg->G_instruct == 0x03)	
		{		
			//先调用直线插补到达起点
			Inverse_Solution();				//反解函数调用
			Line_Interpolation();			//直线插补函数调用
			
			//然后再逆圆弧插补
			Counter_Arc_Interpolation(pGCode_Msg);//逆圆弧插补
		
		}
		word++;			
	}	
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
	 int word = 1;
	 	 
	 /*		给G代码		*/
	 while(word <= 2)
	 {
		 switch (word)
		 {
			 case 1:pcode = "G02X200Y10Z95R20F800";break;
			 case 2:pcode = "G01X200Y10Z120F800";break;			
		 }
		printf("获取代码:%s\r\n",pcode);
	 
	 //译码
		printf("译码\r\n");
		decode(pcode);//译码函数
		printf("pGCode_Msg->G_instruct = %u\r\n",pGCode_Msg->G_instruct);
		
		GetArcO1(pGCode_Msg);//调用求圆心函数
		printf("pGCode_Msg->O_X = %f\r\n",pGCode_Msg->O_X);
		printf("pGCode_Msg->O_Y = %f\r\n",pGCode_Msg->O_Y);

		 x = pGCode_Msg->coor_value[0];
		 y = pGCode_Msg->coor_value[1];
		 z = pGCode_Msg->coor_value[2];
		 printf("x = %f\r\n",x);
		 
	 /************G01	直线插补************/
		if(pGCode_Msg->G_instruct == 0x01)	
		{
				Inverse_Solution();				//反解函数调用
				Line_Interpolation();			//直线插补函数调用
			 
				for(i=0; i < 3; i++) 
				{
					pGCode_Msg->coor_currentValue[i] = pGCode_Msg->coor_value[i];  //保存当前坐标
					printf("pGCode_Msg->coor_currentValue[%d] = %d\r\n",i, pGCode_Msg->coor_currentValue[i]);									
				}

		}
	 
		/*********G02	顺圆弧插补	***********/
		if(pGCode_Msg->G_instruct == 0x02)	
		{
			//先调用直线插补到达起点
			Inverse_Solution();				//反解函数调用
			Line_Interpolation();			//直线插补函数调用
			
			//然后再顺圆弧插补
			Arc_Interpolation(pGCode_Msg);//顺圆弧插补
		
		}
		
		/*********G03	逆圆弧插补	***********/	
		if(pGCode_Msg->G_instruct == 0x03)	
		{		
			//先调用直线插补到达起点
			Inverse_Solution();				//反解函数调用
			Line_Interpolation();			//直线插补函数调用
			
			//然后再逆圆弧插补
			Counter_Arc_Interpolation(pGCode_Msg);//逆圆弧插补
		
		}
		word++;			
	}
}	





/**************************************************************************************************/
/*
 *
 *	函数功能：大臂上仰, 20°
 *
 */
void OnButtonMovedOut_BigUp(WM_MESSAGE * pMsg)					// GUI_ID_BUTTON9
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_Y = 0; PUL_Y = 1; delay_us(800); PUL_Y = 0; delay_us(800);	//大臂上仰，走20度
	}
}	


/*
 *
 *	函数功能：大臂下仰, 20°
 *
 */
void OnButtonMovedOut_BigDown(WM_MESSAGE * pMsg)					// GUI_ID_MAXIMIZE
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_Y = 1; PUL_Y = 1; delay_us(800); PUL_Y = 0; delay_us(800);	//大臂下仰，走20度
	}
}	


/*
 *
 *	函数功能：小臂上仰, 20°
 *
 */
void OnButtonMovedOut_SmallUp(WM_MESSAGE * pMsg)					// GUI_ID_YES
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_Z = 1; PUL_Z = 1; delay_us(800); PUL_Z = 0; delay_us(800);	//小臂上仰，走20度
	}
}	


/*
 *
 *	函数功能：小臂下仰, 20°
 *
 */
void OnButtonMovedOut_SmallDown(WM_MESSAGE * pMsg)					// GUI_ID_NO
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_Z = 0; PUL_Z = 1; delay_us(800); PUL_Z = 0; delay_us(800);	//小臂下仰，走20度
	}
}	


/*
 *
 *	函数功能：底座向左转, 20°
 *
 */
void OnButtonMovedOut_BaseLeft(WM_MESSAGE * pMsg)					// GUI_ID_CLOSE
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_X = 0; PUL_X = 1; delay_us(800); PUL_X = 0; delay_us(800);	//底座顺时针，走20度
	}
}	


/*
 *
 *	函数功能：底座向右转, 20°
 *
 */
void OnButtonMovedOut_BaseRight(WM_MESSAGE * pMsg)					// GUI_ID_HELP
{
	int i3=0;
	for(i3=0; i3<88; i3++)			
	{
		DIR_X = 1; PUL_X = 1; delay_us(800); PUL_X = 0; delay_us(800);	//底座逆时针，走20度
	}
}	





