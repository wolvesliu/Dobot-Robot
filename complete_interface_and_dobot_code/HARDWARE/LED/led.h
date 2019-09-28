#ifndef __LED_H
#define __LED_H
#include "sys.h"

// 端口定义
#define LED0 PFout(9)		// DS0
#define LED1 PFout(10)	// DS1	 

#define PUL_X PCout(5)	// PB5
#define PUL_Y PCout(1)	// PE5	
#define PUL_Z PCout(3)	// PE6
#define DIR_X PCout(4)	// PE7	
#define DIR_Y PCout(0)	// PE8
#define DIR_Z PCout(2)	// PE9 

void LED_Init(void);//初始化		 				    
#endif
