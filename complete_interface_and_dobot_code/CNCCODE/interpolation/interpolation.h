#ifndef __INTERPOLATION_H
#define __INTERPOLATION_H
#include "sys.h"
#include "decode.h"

void Reset_Dobot(void);					//复位函数声明
void Inverse_Solution(void);		//反解函数声明
void Line_Interpolation(void);	//直线插补函数声明

void Counter_Arc_Interpolation(GCode_Msg* pGCode_Msg);	//逆圆弧插补
void Arc_Interpolation(GCode_Msg* pGCode_Msg);					//顺圆弧插补

#endif
