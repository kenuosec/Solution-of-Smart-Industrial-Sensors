#ifndef __EC200_H
#define __EC200_H


#include "system.h"


/*-----------------------   设备证书   -----------------------*/
#define PRODUCTKEY		"a1w3nn8YYOo"
#define DEVICENAME		"car_1"
#define DEVICESECRET		"b92182fa3a62a1c95bcb69398ed58d65"


/*----------------------   上传变量   -------------------------*/
#define DATA_NUM		2
#define DATA1			"power"		
#define DATA2			"status"


typedef struct _ec200_upload ec200_upload_t;

struct _ec200_upload
{
	char 	name[20];
	int		value;
};

/*---------------------   上传变量类型声明   -------------------------*/
typedef struct _ec200_data ec200_data_t;  

struct _ec200_data
{
	char 	name[20];
    int 	value;
};


/*----------------------   标志位   --------------------*/
#define SIM_OK 				0
#define SIM_COMMUNTION_ERR 	0xff
#define SIM_CPIN_ERR 		0xfe
#define SIM_CREG_FAIL 		0xfd
#define SIM_MAKE_CALL_ERR 	0Xfc
#define SIM_ATA_ERR       	0xfb

#define SIM_CMGF_ERR 		0xfa
#define SIM_CSCS_ERR 		0xf9
#define SIM_CSCA_ERR 		0xf8
#define SIM_CSMP_ERR 		0Xf7
#define SIM_CMGS_ERR       	0xf6
#define SIM_CMGS_SEND_FAIL	0xf5

#define SIM_CNMI_ERR 		0xf4
#define BUFLEN 				255

//extern u8 Flag_Rec_Message;	//ÊÕµ½¶ÌÐÅ±êÊ¾


int ec200_self_test(void);
int ec200_mqtt_connect(u8* productkey,u8* devicename,u8* devicesecret);
//int ec200_data_send(u8* productkey,u8* devicename);
int ec200_data_send(u8* productkey,u8* devicename,u8* json);



void check_cmd(void);
u8 EC20_send_cmd(u8 *cmd,u8 *ack,u16 waittime);


#endif

