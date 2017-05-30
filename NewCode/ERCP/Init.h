#ifndef INIT_H_
#define INIT_H_

#include "C8051F500_defs.h"
#include "compiler_defs.h"


void OSCILLATOR_Init (void);
void PORT_Init (void);
void CAN0_Init (void);
void ADC0_Init(void);
void Timer_Init(void);
void CAN0_TransferMO (U8 obj_num);


#define RelayON (P1 &= ~0x40)
#define RelayOFF (P1 |= 0x40)
#define APP_ON ( P2 &= ~0x40)
#define APP_OFF (P2 |= 0x40)
#define REL_ON (P2 &= ~0x80)
#define REL_OFF (P2 |= 0x80)

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
#define IPM_ID 0x001
#define EBV_ID 0x002
#define Broadcast_ID 0x003
#define ERCP_ID 0x010
#define BPCP_ID 0x011
#define CP16_ID 0x012
#define ANALOG_INPUTS    2
#define INT_DEC             256        // Integrate and decimate ratio


bit CAN_ERROR = 0;                     // 0 = No Errors occurred
                                       // 1 = Some error(s) occurred
U8 FaultCode = 0x00;

U8 CAN_Tx_Buf[8] = {0xf1, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
U8 CAN_Rx_Buf[8];
U8 CAN_RX_COMPLETE;                  

SEGMENT_VARIABLE (RESULT[ANALOG_INPUTS], U32, xdata);
U8 PIN_TABLE[ANALOG_INPUTS] = {0x00, 0x01};
U32 accumulator[ANALOG_INPUTS];
U8 AMUX_INPUT = 0;
U8 PWM_Count = 0;
U8 PWM_Period = 100;
U8 PWM_APP = 0;
U8 PWM_REL = 0;

U32 Target_ERT_Pressure;

U32 pressure_current_ERT;
U16 pressureERT_H;
U16 pressureERT_L;
float P_mA_current_ERT=0 ;


U32 pressure_current_MRT;
U16 pressureMRT_H;
U16 pressureMRT_L;
float P_mA_current_MRT=0 ;

float error, sumerror, lasterror, kp, ki, kd;

#endif