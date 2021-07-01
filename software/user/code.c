/*
 *	code.c
 * 	2020-07-31 09:11:01
 * 	
 * 	实现功能: 
 *		函数模版、程序结构。
 *
 *
 *
 *
 */
#include "code.h"
   
   
uint8_t code_a;			/* 全局变量功能 */
uint8_t code_b;			/* 全局变量功能 */


/* ---------------------------- 方法声明 ------------------------------------ */
/* 模块中的函数声明 */
//数据操作
static void code_fun1(uint8_t d1,uint8_t d2);
static void code_fun2(uint8_t d1,uint8_t d2);
static void code_fun3(uint8_t d1,uint8_t d2);
static void code_fun4(uint8_t d1,uint8_t d2);

//设备操作
static void code_device1_init(void);


/* ---------------------------- 设备定义 ------------------------------------ */
/* 外部器件操作接口 */
const xxx_device_t xxxxxxx = 
{
	.init = code_device1_init,

};



/* ---------------------------- 方法实现 ------------------------------------ */
/* 操作实现方法 */
static void code_fun1(uint8_t d1,uint8_t d2)
{
  /*
      code...
  */
}

static void code_fun2(uint8_t d1,uint8_t d2)
{
  /*
      code...
  */
}

static void code_fun3(uint8_t d1,uint8_t d2)
{
  /*
      code...
  */
}

static void code_fun4(uint8_t d1,uint8_t d2)
{
  /*
      code...
  */
}


static void code_device1_init(void)
{
  /*
      code...
  */
}






/* 全局函数 */
void ops_example(void)
{
	code_fun1(code_a,code_b);
	code_fun2(code_a,code_b);
	code_fun3(code_a,code_b);
	code_fun4(code_a,code_b);


}



