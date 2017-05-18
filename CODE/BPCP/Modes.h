#ifndef MODES_H_
#define MODES_H_


#include "compiler_defs.h"
#include "C8051F500_defs.h"            // SFR declarations


void Yunzhuanwei(void);
void Chuzhiwei(void);
void Quanzhidongwei(void);
void Yizhiwei(void);
void Chonglianwei(void);
void Jinjiwei(void);

#define RelayON (P1 &= ~0x40)
#define RelayOFF (P1 |= 0x40)
#define APPON (P2 &= ~0x40)
#define APPOFF (P2 |= 0x40)
#define RELON (P2 &= ~0x10)
#define RELOFF (P2 |= 0x10)

#endif