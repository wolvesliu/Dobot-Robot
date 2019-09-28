#ifndef __DECODE_H
#define __DECODE_H

//解释后的G代码参数
//空间大小:4*3+4*1+2*1+1*1+1*1=20byte;
//字符代码解释后保存
typedef struct {
	
	float coor_value[3]; //G代码 X Y Z
	float O_R;//圆弧插补半径
	float O_X,O_Y;//圆心横纵坐标
	int F;//插补速度
	char G_instruct;//G指令 G00 G01 G02 G03……
	char M_instruct;//M辅助指令
	
	
	long int  coor_currentValue[3]; //当前坐标
}GCode_Msg;


//保存插补过程中的参数
//空间大小：4*3+4*3+4*3+4*1+2*1+1*1+1*1+2*1+4*2=54Byte
typedef struct{
	 //long int  coor_currentValue[3]; //当前坐标
	 long int  coor_originValue[3];	//起点坐标
	 long int coor_destinationValue[3];//终点坐标
	float O_R;//圆弧插补半径
	int F;//插补速度
	char G_instruct;//G指令 G00 G01 G02 G03……
	signed char f;//当前位置与理论位置的偏差
	unsigned int steps;//剩余步数
	//float O_X,O_Y;//圆心横纵坐标
	char humode;//圆弧插补模式0 劣弧 1优弧
	char IS_INTERPOLATINO;//定时器是否正在进行插补过程，0 不是 1 是
} NC_Para;



void decode(char* strcmdbuffer );
void GetArcO1(GCode_Msg* pGCode_Msg);

#endif
