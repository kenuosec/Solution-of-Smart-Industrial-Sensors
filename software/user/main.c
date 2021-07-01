#include "system.h"
#include "include.h"



int errcont = 0;
u8  flag = 1;

char upload[100];	/* 发送消息缓存区 */

/* 发送到阿里云的变量 */
int status = 1;
int power = 100;


int main(void)
{
	
	/*---------------   系统功能配置   ------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	time_init();
	
	
	/*---------------   外设初始化   ------------------*/
	gpio_init();				/* 4G模块控制 */
	uart1_init(115200);			/* 调试信息输出 */
	//uart2_init(115200);			/* 4G模块通信 */
	USART2_Init(115200);         //与4G模块通信
	
	
	printf("\r ************************************************ \r");
	printf("\r 	IOT boart start successfully ! \r");
	printf("\r ************************************************ \r");
	
	
	while(1)
	{
		LED0(ON);
		LED1(ON);
		LED2(ON);
		delay_ms(200);

		LED0(OFF);
		LED1(OFF);
		LED2(OFF);
		delay_ms(200);	
	}

	/*---------------   4G模块硬件检查   ------------------*/
	while(flag)
	{
		flag = ec200_self_test();
		
		LED0(ON);
		delay_ms(1000);
		LED0(OFF);
		delay_ms(1000);
		
		errcont++;
		printf("[WARNING] hardware check %d times.\r\n",errcont);
		if(errcont > 50)
		{
			NVIC_SystemReset();	//超时重启
		}
		
	}
	
	
	/*---------------   连接阿里云   ------------------*/
	errcont = 0;
	flag = 1;
	while(flag)
	{
		flag = ec200_mqtt_connect((u8*)PRODUCTKEY, (u8*)DEVICENAME, (u8*)DEVICESECRET);
		errcont++;
		printf("connecting to aliyun : %d\r\n",errcont);
		if(errcont > 50)
		{
			NVIC_SystemReset();	//超时重启
		}
	}
	printf("Successfully connected to aliyun\r\n");	
	
	
	
	while(1)
	{

		/*---------------   数据发送   ------------------*/
		
		/* 数据处理 */
		if(power == 0)
			power = 100;
		power--;		
		
		sprintf(upload, "{params:{power:%d,status:%d}}", power, status);	
		
		
		if(ec200_data_send((u8 *)PRODUCTKEY, (u8 *)DEVICENAME, (u8 *)upload) < 0)
		{
			delay_ms(2000);
			check_cmd();    //不存储到串口数组清空数据
			memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));
			USART2_RX_STA = 0;
		}
		
		
		/* 接收到数据的处理 */
//		if(USART2_RX_STA&0X8000)		
//		{
//			printf("Recive message from aliyun:");
//			printf((const char*)USART2_RX_BUF,"\r\n");
//			if(strstr((const char*)USART2_RX_BUF,(const char*)"ON"))
//			{
//				LED0(ON);
//				LED1(ON);
//				printf("LED status changed\r\n");
//			}
//			else if(strstr((const char*)USART2_RX_BUF,(const char*)"OFF"))
//			{
//				LED0(OFF);
//				LED1(OFF);
//				printf("LED status changed\r\n");
//			}
//			check_cmd();
//			memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));
//			USART2_RX_STA=0;

//		}	
	}
	
	
}



