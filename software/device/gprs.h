#ifndef __GPRS_H
#define __GPRS_H

#include "system.h"


/*  设备信息  */
#define 	PRODUCT_KEY				"a14iGSy6A0e"		
#define 	PRODUCT_SECRET			"3kJk9PyWqfwgIAMm"
#define 	DEVICE_NAME				"device1"
#define 	DEVICE_SECRET			"aecf5eee46a7a20488714d3387ac2d12"
#define 	VERSION					"xym-1.0.0"



void gprs_net_connect(void);
int gprs_net_check(void);





#endif


