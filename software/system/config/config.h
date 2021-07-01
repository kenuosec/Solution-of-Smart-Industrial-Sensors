#ifndef __CONFIG_H
#define __CONFIG_H	 
#include "sys.h"
#define COOC_VERSION "0001"
#define SECOND_SUCCESS "{\"cmd\":\"20002\",\"v\":\"0001\",\"body\":{\"code\":\"0\"}}*\r\n"
#define SECOND_FAILED "{\"cmd\":\"20002\",\"v\":\"0001\",\"body\":{\"code\":\"1\"}}*\r\n"

#define COMMAND_CODE "cmd"
#define VERSION_CODE "v"
#define BODY_CODE "body"
#define BODY_VELOCITY_CODE "velocity"
#define BODY_L_CODE "l"
#define BODY_R_CODE "r"
#define BODY_POWER_CODE "power"
#define BODY_BATTERY_CODE "battery"
#define BODY_ACC_CODE "acc"
#define BODY_BRAKE_CODE "brake"
#define BODY_STATE_CODE "state"
#define BODY_GEARS_CODE "gears"
#define BODY_GPS_CODE "gps"
#define BODY_DISTANCE_CODE "distance"
#define BODY_ACCXYZ_CODE "accxyz"
#define BODY_VERSION_CODE "version"
#define BODY_FENCE_CODE "fence"
#define BODY_SOUNDTYPE_CODE "soundtype"
#define BODY_SOUNDVOL_CODE "soundvol"
#define BODY_PARENT_CODE "parent"
#define BODY_MAXSPEED_CODE "maxspeed"


#define BODY_VOLUME "volume"
#define BODY_SOUND "sound"
#define BODY_CALIBRATE "calibrate"
#define BODY_GPSX "gpsx"
#define BODY_GPST "gpst"
#define BODY_SPEED "speed"
#define BODY_SCRAM "scram"
#define BODY_GEARS "gears"
typedef struct 
{
	int velocity; //ʵ�ʳ���
	u8 maxspeed;
	int l;				//����ת��
	int r;				//�ҵ��ת��
	int power;		//��ص��� 0-100
	u8 battery;		//���״̬ 0��� 1�ŵ�
	int acc;			//�������
	int brake;		//ɲ�����
	u8 gears;			//�趨��λ 0-5
	int gps_latitude; //gps
	int gps_longitude;
	int distance;		//��ʻ����
	int acc_x;			//������ٶ�
	int acc_y;
	int acc_z;
	int version;		//�汾��
	u8 fence;				//����Χ�� 0�� 1��
	u8 soundtype;		//������Ч
	u8 soundvol;		//��������
	u8 parent;			//�ҳ�ģʽ
		
}CarInfo;
extern CarInfo car_info;
#endif


