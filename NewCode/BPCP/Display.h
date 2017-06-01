#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "compiler_defs.h"
#include "C8051F500_defs.h"

#define uchar unsigned char
#define uint unsigned int


#define Setwela(x)		if(x == 0) P4 &= 0XFD; else P4 |= 0X02
#define Setdula(x)		if(x == 0) P4 &= 0XFE; else P4 |= 0X01

/*
#define SMG_1(x)		if(x == 0) P3 &= ~0X01; else P3 |= 0X01
#define SMG_2(x)		if(x == 0) P3 &= ~0X02; else P3 |= 0X02
#define SMG_3(x)		if(x == 0) P3 &= ~0X04; else P3 |= 0X04
#define SMG_4(x)		if(x == 0) P3 &= ~0X08; else P3 |= 0X08

*/
void smg_display(uchar smg1_dat,uchar smg2_dat,uchar smg3_dat,uchar smg4_dat);

#endif