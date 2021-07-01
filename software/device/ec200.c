#include "ec200.h"

#include "string.h"		/* 字符串操作 */
#include "uart.h"		/* printf */
#include "uart2.h"		/* printf */


/* 通过UART2发送AT指令 */
void ec200_at(u8* command, u8* reply, u16 time)
{
	



}


	



u8 		EC20CSQ[BUFLEN];
char 	ec200_at_buff[255];   /* AT指令缓存 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EC20各项测试(拨号测试、短信测试、GPRS测试)共用代码
//EC20发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)

/* 字符串检索,rx_buff中寻找str */
u8* EC20_check_cmd(u8 *str)
{
    char* strx = 0;
    if(USART2_RX_STA&0X8000)//接收到一次数据了
    {
        USART2_RX_BUF[USART2_RX_STA&0X7FFF] = '\0';
        strx = strstr((const char*)USART2_RX_BUF, (const char*)str);
        printf("ATCMD<-\r\n %s\r\n",USART2_RX_BUF);//发送命令
    }
    return (u8*)strx;
}

void check_cmd(void)
{
    if(USART2_RX_STA&0X8000)		//接收到一次数据了
    {
        USART2_RX_BUF[USART2_RX_STA&0X7FFF] = '\0';//添加结束符
    }
}

//向EC20发送命令
//cmd:发送的命令字符串(不需要添加回车了),当cmd<0XFF的时候,发送数字(比如发送0X1A),大于的时候发送字符串.
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 EC20_send_cmd(u8 *cmd, u8 *ack, u16 waittime)
{
    u8 res = 0;
    USART2_RX_STA = 0;
    if((u32)cmd<=0XFF)
    {
        USART2->DR=(u32)cmd;
    }
	else 
		printf2("%s\r\n",cmd);//发送命令
	
    //printf("ATCMD->\r\n %s\r\n",cmd);//命令显示
	
    if(ack&&waittime)		//需要等待应答
    {
        while(--waittime)	//等待倒计时
        {
            delay_ms(10);
            if(USART2_RX_STA&0X8000)//接收到期待的应答结果
            {
                if(EC20_check_cmd(ack))
					break;//得到有效数据
                USART2_RX_STA = 0;
            }
        }
        if(waittime==0)
			res = 1;
    }
    USART2_RX_STA = 0;
    return res;
}


/* 上电自检 */
int ec200_self_test(void)
{
    u8 status;
	
    memset(EC20CSQ,0,BUFLEN);
	
	/* 通信测试 */
    if(EC20_send_cmd((u8 *)"ATE1", (u8 *)"OK",100))
    {
        if(EC20_send_cmd((u8 *)"ATE1", (u8 *)"OK",100))
		{
			status = SIM_COMMUNTION_ERR;	//通信不上
			goto ec200_status_print;
		}
			
    }
	/* SIM状态 */
    if(EC20_send_cmd((u8*)"AT+CPIN?", (u8*)"READY",400))
	{
		status = SIM_CPIN_ERR;
		goto ec200_status_print;
	}
	/* 网络注册状态检测 */
    if(EC20_send_cmd((u8 *)"AT+CREG?", (u8 *)"0,1",400))	//检测0，1 或者 0，5
    {
        if(strstr((const char*)USART2_RX_BUF,"0,5")==NULL)
        {
            if(!EC20_send_cmd((u8 *)"AT+CSQ",  (u8 *)"OK",200))
            {
                memcpy(EC20CSQ, USART2_RX_BUF + 15,2);
            }
            status = SIM_CREG_FAIL;	//等待附着到网络
			goto ec200_status_print;
        }
    }
	
	status = SIM_OK;	
	
	/* 状态信息输出 */
ec200_status_print:
    switch(status)
    {
    case SIM_OK:        
		printf("Sim card OK\r\n");
        break;
    case SIM_COMMUNTION_ERR:
        printf("Connecting to EC200S...\r\n");
        break;
    case SIM_CPIN_ERR:
        printf("Checking sim card..\r\n");
        break;
    case SIM_CREG_FAIL:
        printf("Register network...\r\n");
	printf("Signal strength:%s",EC20CSQ);
        break;
    default:
        break;
    }
    return status;
}

int ec200_mqtt_connect(u8* productkey, u8* devicename, u8* devicesecret)
{
    if(EC20_send_cmd((u8 *)"AT+CGATT?",(u8 *)": 1",100))	 
		return 1;  //检测激活PDP
    if(EC20_send_cmd((u8 *)"AT+QIACT?",(u8 *)"OK",100))          
		return 2;  //检测激活ACT
    if(EC20_send_cmd((u8 *)"AT+QIDEACT=1",(u8 *)"OK",100))	 
		return 3;  //关闭当前连接
    if(EC20_send_cmd((u8 *)"AT+QMTCLOSE=0",NULL,0))	 
		return 4;  //关闭MQTT客户端
    if(EC20_send_cmd((u8 *)"AT+QMTDISC=0",NULL,0))	 
		return 5;  //关闭和MQTT服务器的所有连接

    //配置进入阿里云
    memset(ec200_at_buff,0,BUFLEN);
    sprintf(ec200_at_buff,"AT+QMTCFG=\"aliauth\",0,\"%s\",\"%s\",\"%s\"\r\n",productkey,devicename,devicesecret);
    if(EC20_send_cmd((u8*)ec200_at_buff,(u8*)"OK",1000))
		return 6;
    //打开阿里云的连接，需要比较久的时间
    if(EC20_send_cmd((u8*)"AT+QMTOPEN=0,\"iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883",(u8 *)"+QMTOPEN: 0,0",3000))
		return 7;

    //连接到阿里云设备
    memset(ec200_at_buff,0,BUFLEN);
    sprintf(ec200_at_buff,"AT+QMTCONN=0,\"%s\"\r\n",devicename);
    if(EC20_send_cmd((u8*)ec200_at_buff,(u8*)"+QMTCONN: 0,0,0",1000))
		return 8;

    //订阅到阿里云
    memset(ec200_at_buff,0,BUFLEN);
    sprintf(ec200_at_buff,"AT+QMTSUB=0,1,\"/%s/%s/user/get\",0 \r\n",productkey,devicename);
    if(EC20_send_cmd((u8 *)ec200_at_buff,(u8 *)"+QMTSUB: 0,1,0,1",1000))	 
		return 9;

    printf("Device has connected to aliyun [..]\r\n");
    return 0;	
}

int ec200_data_send(u8* productkey,u8* devicename,u8* json)
{
    memset(ec200_at_buff,0,BUFLEN);
    sprintf(ec200_at_buff,"AT+QMTPUB=0,0,0,0,\"/sys/%s/%s/thing/event/property/post\"\r\n",productkey,devicename);
    if(EC20_send_cmd((u8*)ec200_at_buff, (u8*)">", 100))                 
		return 1;
    memset(ec200_at_buff,0,BUFLEN);	
	sprintf(ec200_at_buff, "%s", (const char*)json);
    if(EC20_send_cmd((u8 *)ec200_at_buff, NULL, 0))                  
		return 2;
    if(EC20_send_cmd((u8 *)0x1A, (u8 *)"OK", 1500))	
		return 3;
    printf("Sent successfully   [OK]\r\n");
    return -1;
}



