#include "interpolation.h"
#include "sys.h"
#include <math.h>
#include "key.h"
#include "led.h"
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

//L1,L2,L3分别是3个连杆的长度；step_1,step_2,step_3三电机所走的脉冲数（有正有负）；x_term,y_term,z_term三电机所走的脉冲数取了绝对值（都是非负）
//step_sum总步数;x1,y1,z1起点坐标（0,0,0);i_con当前所走的步数；f1,f2,f3直线方程;x,y,z机械臂坐标值；
//angle_Z1,angle_Z2,angle_Z3,angle_Z4角度值；w1,w2,w3,w4,w5,w6反解时用的中间变量；
//start_angle_1,start_angle_2,start_angle_3,start_angle_4开始的角度；motor_angle_1,motor_angle_2,motor_angle_3,motor_angle_4角度差值
		
	int i1,i2,i3,word,step_1,step_2,step_3,step_sum,step_sum1,x_term,y_term,z_term,i_con;
  double f1,f2,f3,angle_Z1,angle_Z2,angle_Z3,angle_Z4,i_con1,x1,y1,z1,motor_angle_1,motor_angle_2,motor_angle_4;		
	double w1,w2,w3,w4,w5,w6;
  double x,y,z;
	double start_angle_1,start_angle_2,start_angle_4;
	double x20,y20,x30,y30,x40,y40,x50,y50;
	double L1 = 113; double L2 = 135; double L3 = 170;	//3个连杆的长度
 
void Reset_Dobot(void)					//复位函数定义
 {
		 while(KEY0 != 0)	{	DIR_X = 0; PUL_X = 0;delay_us(800); PUL_X = 1;delay_us(800);}		//底座复位
		 while(KEY1 != 0)	{	DIR_Y = 0; PUL_Y = 0;delay_us(800); PUL_Y = 1;delay_us(800);}		//大臂复位
		 while(KEY2 != 0)	{	DIR_Z = 1; PUL_Z = 0;delay_us(800); PUL_Z = 1;delay_us(800);}		//小臂复位
		 
		 for(i1=1; i1<3556;i1++)	{DIR_X = 1; PUL_X = 0;delay_us(800); PUL_X = 1;delay_us(800);}		//底座回原点
		 for(i2=1; i2<288; i2++)	{DIR_Y = 1; PUL_Y = 0;delay_us(800); PUL_Y = 1;delay_us(800);}		//大臂回原点
		 for(i3=1; i3<1049;i3++)	{DIR_Z = 0; PUL_Z = 0;delay_us(800); PUL_Z = 1;delay_us(800);}		//小臂回原点
 }
 
 void Inverse_Solution(void)			//反解函数定义
 {
		
		/******反解算法********/			 
				w1 = pow(x,2) + pow(y,2);
				w2 = w1 + pow((z-L1),2);
				w3 = sqrt(w2);
				w4 = atan((z-L1)/sqrt(w1)) * 180 /3.141592654;
				w5 = acos((L2*L2+w2-L3*L3)/(2*w3*L2)) * 180 / 3.141592654;
				w6 = acos((L2*L2+L3*L3-w2)/(2*L2*L3)) * 180 / 3.141592654;

				angle_Z1 = atan(y/x) * 180 /3.141592654;
				angle_Z2 = 90 - (w4 + w5);
				angle_Z3 = 180 - w6;
				angle_Z4 = 90 - angle_Z2 - angle_Z3;
			
		/******************************/ 
			 
			  if(word == 1)					//起点角度
				{
					start_angle_1 = 0;	//初始角度为0,0,0
					start_angle_2 = 0;
					start_angle_4 = 0;
				}
			
			 
				motor_angle_1 = angle_Z1 - start_angle_1;	//角度差值
				motor_angle_2 = angle_Z2 - start_angle_2;
				motor_angle_4 = angle_Z4 - start_angle_4;
				
				start_angle_1 = angle_Z1;									//转动后的角度再当做下一次运动的初始值
				start_angle_2 = angle_Z2;
				start_angle_4 = angle_Z4;
				
				/**  判断电机方向   ************/
				if(motor_angle_1 >= 0)		//说明是逆时针旋转
				{
						DIR_X = 0;
				}
				else
				{
						DIR_X = 1;
				}
				
				if(motor_angle_2 >= 0)		//说明大臂下仰
				{
						DIR_Y = 1;
				}
				else
				{
						DIR_Y = 0;
				}
				
				if(motor_angle_4 >= 0)		//说明小臂上仰
				{
						DIR_Z = 1;
				}
				else
				{
						DIR_Z = 0;
				}
				
				step_1 = motor_angle_1 / 0.0225;		//角度转化为脉冲数
				step_2 = motor_angle_2 / 0.0225;
			  step_3 = motor_angle_4 / 0.0225;
				
				x_term = abs(step_1);								//底座电机应转动的脉冲数，为正数
				y_term = abs(step_2);
				z_term = abs(step_3);
}
 
void Line_Interpolation(void)		//直线插补函数定义
{
			//逐点比较法直线插补
			step_sum = x_term + y_term + z_term;			
			x1 = 0; y1 = 0; z1 = 0;								//初始坐标（0，0，0）
			i_con = 0;
			
			
			//空间直线插补，三轴联动
			while(i_con < step_sum)
			{		
					if(x_term == 0)			//在yz平面内
					{
						f3 = y_term * z1 - z_term * y1;		//yz平面
						if(f3 >= 0)			//向+y方向进给一步
						{
								if(y_term == 0)
								{
									PUL_Z = 0;delay_us(800); PUL_Z = 1;delay_us(800);	
									z1++; 
									i_con++;
								}
								else
								{
									PUL_Y = 0;delay_us(800); PUL_Y = 1;delay_us(800);
									y1++;
									i_con++;
								}					
						}
						else
						{
								PUL_Z = 0;delay_us(800); PUL_Z = 1;delay_us(800);
								z1++; 
								i_con++;
						}
							
					}
					
					else	
					{
						f1 = x_term * y1 - y_term * x1;		//xy平面
						f2 = x_term * z1 - z_term * x1;		//xz平面
						
						if((f1 >= 0) && (f2 >= 0))
						{
								if(x1 == x_term)
								{
									i_con = step_sum;
								}
								else 
								{
									PUL_X = 0;delay_us(800); PUL_X = 1;delay_us(800);
									x1++; 
									i_con++;
								}
						}
					
						else if (f2 < 0) 
						{
								if(z1 == z_term)
								{
									i_con = step_sum;
								}
								else 
								{
									PUL_Z = 0;delay_us(800); PUL_Z = 1;delay_us(800);
									z1++; 
									i_con++;
								}
						}
					
						else if(f1 < 0)
						{
								if(y1 == y_term)
								{
									i_con = step_sum;
								}
								else 
								{
									PUL_Y = 0;delay_us(800); PUL_Y = 1;delay_us(800);
									y1++; 
									i_con++;
								}
						}
					
					}
			}		
}


	

void Counter_Arc_Interpolation(GCode_Msg* pGCode_Msg)	//逆圆弧插补
{
	
	
	
	x20 = pGCode_Msg->coor_value[0] - pGCode_Msg->O_R;				//第二个点
	y20 = pGCode_Msg->coor_value[1] + pGCode_Msg->O_R;

	x30 = pGCode_Msg->coor_value[0] - 2 * pGCode_Msg->O_R;		//第三个点
	y30 = pGCode_Msg->coor_value[1];
	
	x40 = pGCode_Msg->coor_value[0] - pGCode_Msg->O_R;				//第四个点
	y40 = pGCode_Msg->coor_value[1] - pGCode_Msg->O_R;
	
	x50 = pGCode_Msg->coor_value[0];
	y50 = pGCode_Msg->coor_value[1];
	
	GetArcO1(pGCode_Msg);		//调用求圆心函数
	printf("pGCode_Msg->O_X = %f\r\n",pGCode_Msg->O_X);
	printf("pGCode_Msg->O_Y = %f\r\n",pGCode_Msg->O_Y);
	
	printf("pGCode_Msg->O_R:%f\r\n",pGCode_Msg->O_R);//打印半径
	


	i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
	step_sum1 = 2 * pGCode_Msg->O_R;

	while(i_con1 < step_sum1)		//	第一个1/4圆												//终点判别，当当前步数小于总步数时，继续循环
	{										
			f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;				//xy平面	圆心（80,80）半径20，圆弧方程					
			if(f1 >= 0)							//点在圆外，应该向-x进给一步，一步为0.3			
			{
					if(x == x20)
					{
						i_con1 = step_sum1;
					}
					else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
					{		
						x = x - 0.3;			//（99.7,80,50）
						y = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y;
						
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						
						i_con1 = i_con1 + 0.3;									//当前步数加0.3；
					}
			}									
			else 						//点在圆内，应该向+y进给一步		
			{
					if(y == y20)
					{
						i_con1 = step_sum1;
					}
					else 
					{	
						y = y + 0.3;		//向+y进给一步
						x = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X;
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加1；0.3
					}										
			}
		}
	
		x = x20; y = y20;		//加工动点坐标							//起始点（100，80,50）
		i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
//		step_sum1 = 2 * pGCode_Msg->O_R;						//圆心（80，80）；圆弧插补的总步数为step_sum1

		//空间圆弧插补，三轴联动
		while(i_con1 < step_sum1)	//	第二个1/4圆												//终点判别，当当前步数小于总步数时，继续循环
		{										
				f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					
				if(f1 >= 0)							//点在圆外，应该向-y进给一步，一步为0.3			
				{
						if(y == y30)
						{
							i_con1 = step_sum1;
						}
						else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
						{		
							y = y - 0.5;			//（99.7,80,50）	
							x = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加0.3；
						}
				}
				
				else 						//点在圆内，应该向-x进给一步		
				{
						if(x == x30)
						{
							i_con1 = step_sum1;
						}
						else 
						{	
							x = x - 0.5;		//向+y进给一步	
							y = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加1；0.3
						}										
				}
		}				
		
		
		x = x30; y = y30;		//加工动点坐标							//起始点（100，80,50）
		i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
//		step_sum1 = 2 * r;						//圆心（80，80）；圆弧插补的总步数为step_sum1

		//空间圆弧插补，三轴联动
		while(i_con1 < step_sum1)	//	第三个1/4圆													//终点判别，当当前步数小于总步数时，继续循环
		{										
				f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					

				if(f1 >= 0)							//点在圆外，应该向+x进给一步，一步为0.3			
				{
						if(x == x40)
						{
							i_con1 = step_sum1;
						}
						else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
						{		
							x = x + 0.5;			//（99.7,80,50）
							y = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加0.3；
						}
				}
				
				else 						//点在圆内，应该向-y进给一步		
				{
						if(y == y40)
						{
							i_con1 = step_sum1;
						}
						else 
						{	
							y = y - 0.5;		//向+y进给一步	
							x = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加1；0.3
						}										
				}
		}				
		
		
		x = x40; y = y40; 		//加工动点坐标							//起始点（100，80,50）
		i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
//		step_sum1 = 2 * r;						//圆心（80，80）；圆弧插补的总步数为step_sum1
		//空间圆弧插补，三轴联动
		while(i_con1 < step_sum1)	//	第四个1/4圆															//终点判别，当当前步数小于总步数时，继续循环
		{										
				f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					

				if(f1 >= 0)							//点在圆外，应该向+y进给一步，一步为0.3			
				{
						if(y == y50)
						{
							i_con1 = step_sum1;
						}
						else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
						{		
							y = y + 0.5;			//（99.7,80,50）
							x = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加0.3；
						}
				}
				
				else 						//点在圆内，应该向+x进给一步		
				{
						if(x == x50)
						{
							i_con1 = step_sum1;
						}
						else 
						{	
							x = x + 0.5;		//向+y进给一步	
							y = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x -  pGCode_Msg->O_X) * (x -  pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
							Inverse_Solution();				//反解函数调用
							Line_Interpolation();			//直线插补函数调用		
							i_con1 = i_con1 + 0.5;									//当前步数加1；0.3
						}										
				}
		}				
		
		
}


void Arc_Interpolation(GCode_Msg* pGCode_Msg)			//顺圆弧插补
{
	x20 = pGCode_Msg->coor_value[0] + pGCode_Msg->O_R;				//第二个点
	y20 = pGCode_Msg->coor_value[1] + pGCode_Msg->O_R;

	x30 = pGCode_Msg->coor_value[0] + 2 * pGCode_Msg->O_R;		//第三个点
	y30 = pGCode_Msg->coor_value[1];
	
	x40 = pGCode_Msg->coor_value[0] + pGCode_Msg->O_R;				//第四个点
	y40 = pGCode_Msg->coor_value[1] - pGCode_Msg->O_R;
	
	x50 = pGCode_Msg->coor_value[0];
	y50 = pGCode_Msg->coor_value[1];
	
	GetArcO1(pGCode_Msg);		//调用求圆心函数
	printf("pGCode_Msg->O_X = %f\r\n",pGCode_Msg->O_X);
	printf("pGCode_Msg->O_Y = %f\r\n",pGCode_Msg->O_Y);
	
	printf("pGCode_Msg->O_R:%f\r\n",pGCode_Msg->O_R);//打印半径
	
	
	
	i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
	step_sum1 = 2 * pGCode_Msg->O_R;						//圆心（80，80）；圆弧插补的总步数为step_sum1
	//空间圆弧插补，三轴联动
	while(i_con1 < step_sum1)			//	第一个1/4圆												//终点判别，当当前步数小于总步数时，继续循环
	{										
			f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;				//xy平面	圆心（80,80）半径20，圆弧方程					
			if(f1 >= 0)							//点在圆外，应该向+x进给一步，一步为0.3			
			{
					if(x == x20)
					{
						i_con1 = step_sum1;
					}
					else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
					{		
						x = x + 0.3;			//（99.7,80,50）											
						y = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y;
						
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						
						i_con1 = i_con1 + 0.3;									//当前步数加0.3；
						
					}
			}									
			else 						//点在圆内，应该向+y进给一步		
			{
					if(y == y20)
					{
						i_con1 = step_sum1;
					}
					else 
					{	
						y = y + 0.3;		//向+y进给一步
						x = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X;
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加1；0.3
					}										
			}
}
	

	i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
	//空间圆弧插补，三轴联动
	while(i_con1 < step_sum1)			//	第二个1/4圆											//终点判别，当当前步数小于总步数时，继续循环
	{										
			f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					
			if(f1 >= 0)							//点在圆外，应该向-y进给一步，一步为0.3			
			{
					if(y == y30)
					{
						i_con1 = step_sum1;
					}
					else						 		//向-y进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
					{		
						y = y - 0.3;			//（99.7,80,50）	
						x = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加0.3；
					}
			}
			
			else 						//点在圆内，应该向+x进给一步		
			{
					if(x == x30)
					{
						i_con1 = step_sum1;
					}
					else 
					{	
						x = x + 0.3;		//向+y进给一步	
						y = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加1；0.3
					}										
			}
	}

		
	i_con1 = 0;																						//圆弧插补的当前步数为i_con1			
	//空间圆弧插补，三轴联动
	while(i_con1 < step_sum1)			//	第三个1/4圆											//终点判别，当当前步数小于总步数时，继续循环
	{										
			f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					

			if(f1 >= 0)							//点在圆外，应该向-x进给一步，一步为0.3			
			{
					if(x == x40)
					{
						i_con1 = step_sum1;
					}
					else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
					{		
						x = x - 0.3;			//（99.7,80,50）
						y = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加0.3；
					}
			}
			
			else 						//点在圆内，应该向-y进给一步		
			{
					if(y == y40)
					{
						i_con1 = step_sum1;
					}
					else 
					{	
						y = y - 0.3;		//向+y进给一步	
						x = abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.3;									//当前步数加1；0.3
					}										
			}
	}	
	
	
	i_con1 = 0;																						//圆弧插补的当前步数为i_con1	
	//空间圆弧插补，三轴联动
	while(i_con1 < step_sum1)		//	第三个1/4圆													//终点判别，当当前步数小于总步数时，继续循环
	{										
			f1 = (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X) + (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y) - pGCode_Msg->O_R * pGCode_Msg->O_R;					//xy平面	圆心（80,80）半径20，圆弧方程					

			if(f1 >= 0)							//点在圆外，应该向+y进给一步，一步为0.3			
			{
					if(y == y50)
					{
						i_con1 = step_sum1;
					}
					else						 		//向-x进给一步,一步为0.3；x、y与i_con1的变化要一致，经过测试 最好的一组数据为0.3
					{		
						y = y + 0.5;			//（99.7,80,50）
						x = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (y - pGCode_Msg->O_Y) * (y - pGCode_Msg->O_Y))) + pGCode_Msg->O_X; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.5;									//当前步数加0.3；
					}
			}
			
			else 						//点在圆内，应该向-x进给一步		
			{
					if(x == x50)
					{
						i_con1 = step_sum1;
					}
					else 
					{	
						x = x - 0.5;		//向+y进给一步	
						y = (-1) * abs(sqrt(pGCode_Msg->O_R * pGCode_Msg->O_R - (x - pGCode_Msg->O_X) * (x - pGCode_Msg->O_X))) + pGCode_Msg->O_Y; 
						Inverse_Solution();				//反解函数调用
						Line_Interpolation();			//直线插补函数调用		
						i_con1 = i_con1 + 0.5;									//当前步数加1；0.3
					}										
			}
	}			


}

