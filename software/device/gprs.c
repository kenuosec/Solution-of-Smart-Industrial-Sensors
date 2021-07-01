#include "gprs.h"
#include "gpio.h"
#include "uart.h"



void gprs_net_connect(void)
{
	printf2("[INFO]:The network is connecting.");
	while(PBin(1) != 1) 	/* 等待网络连接 */
	{
		printf2("=");
		delay_ms(200);
    }
	printf2(">>\n");
	printf2("[INFO]:The network is connected!\n");
}
	
/**
 * 网络状态检查.
 * 检查GPRS模块当前的连接状态，如果断开，输出调试信息.
 *
 * @return  0 - 连接正常, -1 - 连接断开
 */
int gprs_net_check(void)
{
	if(PBin(1) == 1)
		return 0;
	else	/* 连接断开 */
	{	
		printf2("[ERROR]:The network is disconnected!\n");
		return 1;
	}
}





