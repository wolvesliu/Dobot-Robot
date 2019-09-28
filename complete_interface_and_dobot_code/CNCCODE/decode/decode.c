#include "decode.h"
#include "sys.h"
#include "usart.h"	
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stdbool.h"

//调试选择 1插补使用串口输出调试 0不使用
#define USE_INTER_DEBUG (1)

#if  USE_INTER_DEBUG

#endif

#define NUM_AXIS 4
char axis_codes1[NUM_AXIS]= {'X', 'Y', 'Z', 'F'};//轴在G代码中的关键字

char *strchr_pointer; // just a pointer to find chars in the cmd string like X, Y, Z, E, etc 
GCode_Msg* pGCode_Msg;
int i = 0;


//函数：code_value
//功能：获取字符串中指定字符指针strchr_pointer后面的数字参数，用于获取G代码参数值
//输入：关键字的指针strchr_pointer
//返回：G代码中关键字后面的数值
 float code_value1(char* strchr_pointer) 
{ 
	#if  USE_INTER_DEBUG
	printf("0------%s\r\n",(const char*)strchr_pointer);
	printf("1------%f\r\n",(float)strtod((const char*)(strchr_pointer+1),NULL));
	printf("2------%f\r\n",strtod("1.34569",NULL));
	#endif
	
	return ((float)strtod((strchr_pointer+1), NULL));
}


//函数：code_seen
//功能：查找字符串strcmdbuffer中的关键字code
//输入：关键字code
//返回：查找到关键字1 否则0
 bool code_seen1(char code,char *strcmdbuffer)
	{
		strchr_pointer = strchr(strcmdbuffer, (int)code);
		
	#if  USE_INTER_DEBUG
		printf("code_seen找到%c %d\r\n",code,(strchr_pointer != NULL));
		printf("code_seen找到%s\r\n",(char*)(strchr_pointer) );
	#endif
	
		return ((strchr_pointer != NULL));	//Return True if a character was found
	}

	
//函数：get_coordinatesValue
//功能：查找字符串strcmdbuffer中的坐标值 XYZ R
//输入：字符串strcmdbuffer 参数结构体指针pNC_Para
//输出：G代码信息结构体指针pGCode_Msg
 void get_coordinatesValue1(char* strcmdbuffer,GCode_Msg* pGCode_Msg)
 {
	 int i;

	#if  USE_INTER_DEBUG
		printf("get_coordinatesValues输入%s\r\n",(char*)(strcmdbuffer) );
	#endif
	
	
	 
	 //解释保存坐标值 XYZ
 	 for(i=0; i < NUM_AXIS; i++) 
	 {
			if(code_seen1(axis_codes1[i],strcmdbuffer)) 
			{
					#if  USE_INTER_DEBUG
						printf("111--:%c %s\r\n",axis_codes1[i],(char*)strchr_pointer);
					#endif
				pGCode_Msg->coor_value[i]= (float)code_value1(strchr_pointer);//+ (axis_relative_modes[i] || relative_mode)*current_position[i];
			
				
		
			}
			else //pGCode_Msg->coor_value[i] = pNC_Para->coor_currentValue[i];      //Are these else lines really needed?
				pGCode_Msg->coor_value[i] = pGCode_Msg->coor_value[i]; 
			
			//printf("pGCode_Msg->coor_value[%d] = %f\r\n",i,(float)code_value1(strchr_pointer));
			
			//printf("pGCode_Msg->coor_value[%d] = %f\r\n",i,pGCode_Msg->coor_value[i]);
	 }
	 
	
	 
	//解释保存半径 R
	 if(code_seen1('R',strcmdbuffer))
		{
			pGCode_Msg->O_R=code_value1(strchr_pointer);
		}
		
	 if(code_seen1('F',strcmdbuffer))//保存速度F
	 {
			 pGCode_Msg->F = code_value1(strchr_pointer);
	 }
		
 }
	

//函数：decode
//功能：对一行字符指令进行译码，译码得到的信息保存在pGCode_Msg结构体中
//输入：字符串strcmdbuffer 
//输出：G代码信息结构体指针pGCode_Msg
void decode(char* strcmdbuffer )
{
	
	#if  USE_INTER_DEBUG
		printf("DECODE---%s\r\n",strcmdbuffer);
	#endif
	if(code_seen1('G',strcmdbuffer))//G??
   {
		 	
	#if  USE_INTER_DEBUG
	   printf("22222G:%d\r\n",(int)code_value1(strchr_pointer));
	#endif

      switch((int)code_value1(strchr_pointer))
      {
				
				case 0: // G0
				case 1: // G1
				{
#include <stm32f4xx.h>
						pGCode_Msg->G_instruct=0x01;
						get_coordinatesValue1(strcmdbuffer,pGCode_Msg);//获取 XYZR 坐标值
						break;
				} 
				 case 2://G2 顺圆弧插补
				{
					 pGCode_Msg->G_instruct=0x02;
					get_coordinatesValue1(strcmdbuffer,pGCode_Msg);//获取 XYZR 坐标值
					 break;
				}

				 case 3://G3 逆圆弧插补
				{
						 pGCode_Msg->G_instruct=0x03;
						get_coordinatesValue1(strcmdbuffer,pGCode_Msg);//获取 XYZR 坐标值
					 break;
				}		 
      }
   }
	 else if(code_seen1('M',strcmdbuffer))//保存M指令
	 {
			pGCode_Msg->M_instruct=(int)code_value1(strchr_pointer);;
	 }
	 else if(code_seen1('F',strcmdbuffer))//保存速度F
	 {
			 pGCode_Msg->F = code_value1(strchr_pointer);
	 }
	
	 //打印译码之后的x,y,z坐标、半径R、速度F	 
	 #if  USE_INTER_DEBUG
	   for(i=0;i<4;i++)
		{
			printf("pGCode_Msg->coor_value[%d]:%f\r\n",i,pGCode_Msg->coor_value[i]);
		}
		
		printf("pGCode_Msg->O_R:%f\r\n",pGCode_Msg->O_R);
		
		printf("pGCode_Msg->F:%d\r\n",pGCode_Msg->F);
	#endif

}


// //函数：quad_test
// //功能：插补方式G_instruct下x,y所在象限
// //输入：坐标点x,y 插补方式G_instruct
// //返回：象限值
int quad_test2(float x,float y,char G_instruct)
{
 	switch(G_instruct)
 		{
		case 0x02:
			if((x>0&&y>=0))//||(x==0&&y==0))      //quad 1 and (0,0)point	and x+axis
			return (1);

			if(x<=0&&y>0)                      //quad 2	and y+axis
				return (2);
		
				 if(x<0&&y<=0)                      //quad 3 and x-axis	
					return (3);
							
					 if(x>=0&&y<0)                      //quad 4	and y-axis
						return (4);
				break;
					 
		case 0x03:
			if((x>=0&&y>0))//||(x==0&&y==0))      //quad 1 and (0,0)point	and x+axis
			return (1);

			if(x<0&&y>=0)                      //quad 2	and y+axis
				return (2);
		
				 if(x<=0&&y<0)                      //quad 3 and x-axis	
					return (3);
							
					 if(x>0&&y<=0)                      //quad 4	and y-axis
						return (4);
				break;
					 
 		case 0x01:	//直线插补；其实直线插补不需要知道象限值，直接插补就可以了
			if((x>0&&y>=0))//||(x==0&&y==0))      //quad 1 and (0,0)point	and x+axis
				return (1);

			if(x<=0&&y>0)                      //quad 2	and y+axis
				return (2);
		
			if(x<0&&y<=0)                      //quad 3 and x-axis	
				return (3);
							
			if(x>=0&&y<0)                      //quad 4	and y-axis
	return (4);
		}

		return 0;
}




//函数：GetArcO
//功能：获取圆弧插补的圆心坐标，装载到插补参数结构体pNC_Para
//输入：插补参数结构体指针pNC_Para
//输出：插补参数结构体指针pNC_Para中的圆心值O_X O_Y
//调用步数函数GetSteps1 
void GetArcO1(GCode_Msg* pGCode_Msg)
{
	if(pGCode_Msg->G_instruct == 0x03)	//G03	逆圆弧插补	
	{
		pGCode_Msg->O_X = pGCode_Msg->coor_value[0] - pGCode_Msg->O_R;
		pGCode_Msg->O_Y = pGCode_Msg->coor_value[1];		
	}
	
	else if(pGCode_Msg->G_instruct == 0x02)
	{
		pGCode_Msg->O_X = pGCode_Msg->coor_value[0] + pGCode_Msg->O_R;
		pGCode_Msg->O_Y = pGCode_Msg->coor_value[1];	
	}
	
}

