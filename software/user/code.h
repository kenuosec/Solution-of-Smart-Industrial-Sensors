/*
 *	code.h
 * 	2020-07-31 09:11:01
 * 	
 *
 */
#ifndef __CODE_H
#define __CODE_H


#include "system.h"

   
/*-----------------------------      类型前置声明       ---------------------------*/
typedef struct _xxx_device xxx_device_t;

struct _xxx_device
{
    void (*init)(void);

};


/*-----------------------------      外部接口声明       ---------------------------*/

extern const xxx_device_t xxx; 
void ops_example(void);




#endif /* __CODE_H */


