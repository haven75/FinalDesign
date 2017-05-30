//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "compiler_defs.h"
#include "C8051F500_defs.h"            // SFR declarations
#include "Display.h"

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

typedef union UU64
{
   U32 U32[2];
   U16 U16[4];
   U8 U8[8];
} UU64;

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void OSCILLATOR_Init (void);
void PORT_Init (void);
void CAN0_Init (void);
void ADC0_Init(void);
void Timer_Init(void);
void CAN0_TransferMO (U8 obj_num);

void PressureCal();
void PIDControl();



void Yunzhuanwei(void);
void Chuzhiwei(void);
void Quanzhidongwei(void);
void Yizhiwei(void);
void Chonglianwei(void);
void Jinjiwei(void);

INTERRUPT_PROTO (CAN0_ISR, INTERRUPT_CAN0);
INTERRUPT_PROTO (TIMER0_ISR, INTERRUPT_TIMER0);
INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);
INTERRUPT_PROTO (TIMER3_ISR, INTERRUPT_TIMER3);
INTERRUPT_PROTO (ADC0_ISR, INTERRUPT_ADC0_EOC);

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define SYSCLK       24000000          // System clock speed in Hz
#define MESSAGE_OBJECTS    32          // Number of message objects to use
                                       // Range is 1-32
#define MESSAGE_SIZE        8          // Size in bytes of each CAN message
                                       // Range is 1-8

//-----------------------------------------------------------------------------
// Bit Definition Masks
//-----------------------------------------------------------------------------

// CAN0STAT
#define BOff  0x80                     // Busoff Status
#define EWarn 0x40                     // Warning Status
#define EPass 0x20                     // Error Passive
#define RxOk  0x10                     // Receive Message Successfully
#define TxOk  0x08                     // Transmitted Message Successfully
#define LEC   0x07                     // Last Error Code


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

U32 Target_ERT_Pressure  ;

U32 pressure_current_ERT;
U16 pressureERT_H;
U16 pressureERT_L;
float P_mA_current_ERT=0 ;


U32 pressure_current_MRT;
U16 pressureMRT_H;
U16 pressureMRT_L;
float P_mA_current_MRT=0 ;

float error, sumerror, lasterror, kp, ki, kd;
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void)
{

   SFRPAGE = ACTIVE_PAGE;              // Set for PCA0MD

   PCA0MD &= ~0x40;                    // Disable Watchdog Timer

   OSCILLATOR_Init ();                 // Initialize oscillator
   PORT_Init ();                       // Initialize crossbar and GPIO
   CAN0_Init ();                       // Start CAN peripheral
   ADC0_Init ();
   Timer_Init ();
   RESULT[0]=0;
	 RESULT[1]=0;

	 EIE1 |= 0x40;
   EIE2 |= 0x02;                       // Enable CAN interupts
   EA = 1;                             // Enable global interrupts
   P2 |= 0xC0;
   while (1)
   {
   	 smg_display(0xe,0xa,0xc,18);
		 PressureCal();
   }
}



void OSCILLATOR_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0x87;                      // Set internal oscillator divider to 1

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------

void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE  = CONFIG_PAGE;             // Port SFR's on Configuration page
	
	 P0SKIP |= 0x01;                     // Skip P0.0 (VREF)
	 P0MDIN &= ~0x01;                   // Set VREF to analog
   P0MDOUT  |= 0x40;                   // P0.6 (CAN0 TX) is push-pull
   P1MDOUT  |= 0x08;                   // P1.3 (LED) is push-pull
   P1MDOUT &= 0xbf;          					//P1^6 open drain for relay
	 P2SKIP |= 0x0f;                     // Skip P2.0,P2.1,P2.2,P2.3(ADC input)
	 P2MDIN &= ~0x0f;                   // Set P2.0,P2.1,P2.2,P2.3 as an analog input
   P2MDOUT |= 0xc0;                    //P2.6/7 for driving mosfet
   P3MDOUT |= 0xff;                            //P3 is push-pull to drive the LED.
   P4MDOUT |= 0x03;                            //P4   

   XBR0     = 0x02;                    // Enable CAN0 on Crossbar
   XBR2     = 0x40;                    // Enable Crossbar and weak pull-ups

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   // Initialize the Gain to account for a 5V input and 2.25 VREF
   // Solve the equation provided in Section 9.3.1 of the Datasheet

   // The 5V input is scaled by a factor of 0.44 so that the maximum input
   // voltage seen by the pin is 2.2V

   // 0.44 = (GAIN/4096) + GAINADD * (1/64)

   // Set GAIN to 0x6CA and GAINADD to 1
   // GAIN = is the 12-bit word formed by ADC0GNH[7:0] ADC0GNL[7:4]
   // GAINADD is bit ADC0GNA.0

   ADC0CF |= 0x01;                     // Set GAINEN = 1
   ADC0H   = 0x04;                     // Load the ADC0GNH address
   ADC0L   = 0x6C;                     // Load the upper byte of 0x6CA to 
                                       // ADC0GNH
   ADC0H   = 0x07;                     // Load the ADC0GNL address
   ADC0L   = 0xA0;                     // Load the lower nibble of 0x6CA to 
                                       // ADC0GNL
   ADC0H   = 0x08;                     // Load the ADC0GNA address
   ADC0L   = 0x01;                     // Set the GAINADD bit
   ADC0CF &= ~0x01;                    // Set GAINEN = 0

   ADC0CN = 0x03;                      // ADC0 disabled, normal tracking,
                                       // conversion triggered on TMR2 overflow
                                       // Output is right-justified

   REF0CN = 0x33;                      // Enable on-chip VREF and buffer
                                       // Set voltage reference to 2.25V

   ADC0MX = 0x0A;                      // Set ADC input to P1.2

   ADC0CF = ((SYSCLK / 3000000) - 1) << 3;   // Set SAR clock to 3MHz

   EIE1 |= 0x04;                       // Enable ADC0 conversion complete int.

   AD0EN = 1;                          // Enable ADC0

   SFRPAGE = SFRPAGE_save;
}


//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
void Timer_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;
 
    CKCON = 0x00;			//t1 t0 use the sys-clock/12,t3 t2 refer to TMRXCN
    
   TCON      = 0x00;			//t1 don't run temporarily,t0 don't run 
   TMOD      = 0x21;			//t1 8bit reload timer,t0 16bit timer
   TL0       = 0x90;	
   TH0       = 0xE8;			//3ms,based on 2MHz clock        		×¨ó?óú??DD?D?óê??üá?3ms?¨ê±
   TR0 = 1;
   ET0 = 1;

   TMR2CN = 0x00;                      // Stop Timer2; Clear TF2;
                                       // use SYSCLK as timebase, 16-bit
                                       // auto-reload
   CKCON |= 0x10;                      // Select SYSCLK for timer 2 source
   TMR2RL = 65535 - (SYSCLK / 10000);  // Init reload value for 10 us
   TMR2 = 0xFFFF;                      // Set to reload immediately
   ET2 = 1;                            // Enable Timer2 interrupts
   TR2 = 1;                            // Start Timer2

   PT2 = 1;

		TMR3CN    = 0x00;			//t3 16bit reload timer,don't run,sys-clock/12
    TMR3RLL   = 0x30;
    TMR3RLH   = 0xF8;
    TMR3L     = 0x30;
    TMR3H     = 0xF8;			//    ó?óúS￡?ms?¨ê± */
		TMR3CN |= 0x04;				//run timer3

   SFRPAGE = SFRPAGE_save;
}
//-----------------------------------------------------------------------------
// CAN0_Init
//-----------------------------------------------------------------------------
void CAN0_Init (void)
{
   U8 iter;

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C

   CAN0CN |= 0x01;                     // Start Intialization mode

   //---------Initialize general CAN peripheral settings

   CAN0CN |= 0x4E;                     // Enable Status, Error,
                                       // Module Interrupts
                                       // Enable access to bit timing register

   // See the CAN Bit Timing Spreadsheet for how to calculate this value
   CAN0BT = 0x1402;                    // Based on 24 Mhz CAN clock, set the
                                       // CAN bit rate to 1 Mbps

   //---------Initialize settings common to all message objects

   // Command Mask Register
   CAN0IF1CM = 0x00F0;                 // Write Operation
                                       // Transfer ID Mask, MDir, MXtd
                                       // Transfer ID, Dir, Xtd, MsgVal
                                       // Transfer Control Bits
                                       // Don't set TxRqst or transfer data

   // Mask Registers
   CAN0IF1M1 = 0x0000;                 // Mask Bits 15-0 not used for filtering
   CAN0IF1M2 = 0x5FFC;                 // Ignore Extended Identifier for
                                       // filtering
                                       // Used Direction bit for filtering
                                       // Use ID bits 28-18 for filtering

   // Arbitration Registers
   CAN0IF1A1 = 0x0000;                 // 11-bit ID, so lower 16-bits not used

   // Message Control Registers
   CAN0IF1MC = 0x1480 | MESSAGE_SIZE;  // Enable Receive Interrupt
                                       // Message Object is a Single Message
                                       // Message Size set by #define


   //---------Initialize unique settings for Rx message object

   // Arbitration Registers
   CAN0IF1A2 = 0x8000 | (ERCP_ID << 2);  // Set MsgVal to valid
                                         // Set Object Direction to read
                                         // Set 11-bit Identifier to iter

   CAN0IF1CR = ERCP_ID;                // Start command request

      while (CAN0IF1CRH & 0x80) {}       // Poll on Busy bit


   CAN0IF1A2 = 0x8000 | (Broadcast_ID << 2);  // Set MsgVal to valid
                                         // Set Object Direction to read
                                         // Set 11-bit Identifier to iter

   CAN0IF1CR = Broadcast_ID;                // Start command request

      while (CAN0IF1CRH & 0x80) {}       // Poll on Busy bit
   // Message Control Registers
   CAN0IF1MC = 0x0080 | MESSAGE_SIZE;  // Disable Transmit Interrupt
                                       // Message Object is a Single Message
                                       // Message Size set by #define

   //---------Initialize unique settings for Tx message object
   // Arbitration Registers
   CAN0IF1A2 = 0xA000 | (BPCP_ID << 2);  // Set MsgVal to valid
                                         // Set Direction to write
                                         // Set 11-bit Identifier to iter

   CAN0IF1CR = BPCP_ID;                // Start command request

   while (CAN0IF1CRH & 0x80) {}       // Poll on Busy bit

   CAN0IF1A2 = 0xA000 | (IPM_ID << 2);  // Set MsgVal to valid
                                         // Set Direction to write
                                         // Set 11-bit Identifier to iter

   CAN0IF1CR = IPM_ID;                // Start command request

   while (CAN0IF1CRH & 0x80) {}       // Poll on Busy bit
   //---------Initialize settings for unused message objects

   for (iter = 0; iter < MESSAGE_OBJECTS; iter++)
   {
   	if(iter != ERCP_ID && iter != BPCP_ID && iter != Broadcast_ID && iter != IPM_ID)
	 {
      // Set remaining message objects to be Ignored
      CAN0IF1A2 = 0x0000;              // Set MsgVal to 0 to Ignore
      CAN0IF1CR = iter;                // Start command request

      while (CAN0IF1CRH & 0x80) {}     // Poll on Busy bit
	  }
   }

   CAN0CN &= ~0x41;                    // Return to Normal Mode and disable
                                       // access to bit timing register

   SFRPAGE = SFRPAGE_save;
}

void CAN0_TransferMO (U8 obj_num)
{
   // This function assumes that the message object is fully initialized
   // in CAN0_Init and so all it has to do is fill the data registers and
   // initiate transmission

   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE  = CAN0_PAGE;               // All CAN register are on page 0x0C

   // Initialize all 8 data bytes even though they might not be sent
   // The number to send was configured earlier by setting Message Control

   CAN0IF1DA1L = *CAN_Tx_Buf;              // Initialize data registers based
   CAN0IF1DA1H = *(CAN_Tx_Buf + 1);          // on message object used
   CAN0IF1DA2L = *(CAN_Tx_Buf + 2);
   CAN0IF1DA2H = *(CAN_Tx_Buf + 3);
   CAN0IF1DB1L = *(CAN_Tx_Buf + 4);
   CAN0IF1DB1H = *(CAN_Tx_Buf + 5);
   CAN0IF1DB2L = *(CAN_Tx_Buf + 6);
   CAN0IF1DB2H = *(CAN_Tx_Buf + 7);

   CAN0IF1CM = 0x0087;                 // Set Direction to Write
                                       // Write TxRqst, all 8 data bytes

   CAN0IF1CR = obj_num;                // Start command request

   while (CAN0IF1CRH & 0x80) {}        // Poll on Busy bit

   SFRPAGE = SFRPAGE_save;
}

//Calculate the pressure detect by ADC

void PressureCal()
{
	P_mA_current_ERT=((((( RESULT[1]/4095.0*1000)*1.5*10)/3.0))/250.0);
	pressure_current_ERT=(int)(62.5*P_mA_current_ERT-243.0);//单位KPa	
	pressureERT_H=((pressure_current_ERT/1000)<<4)|(pressure_current_ERT%1000/100);
	pressureERT_L=((pressure_current_ERT%100/10)<<4)|(pressure_current_ERT%10);	

	P_mA_current_MRT=((((( RESULT[0]/4095.0*1000)*1.5*10)/3.0))/250.0);
	pressure_current_MRT=(int)(62.5*P_mA_current_MRT-243.0);//单位KPa
	pressureMRT_H=((pressure_current_MRT/1000)<<4)|(pressure_current_MRT%1000/100);
	pressureMRT_L=((pressure_current_MRT%100/10)<<4)|(pressure_current_MRT%10);
}


//Calculate the PID output
void PIDControl()
{	
	float derror, Uout;
	error = Target_ERT_Pressure - pressure_current_ERT/100.0;  
	sumerror += error;
	derror = error - lasterror;
	lasterror = error;
	
	Uout = kp * error + ki * sumerror + kd * derror;
	
	if(Uout > 0 || Uout == 0)
	{
		Uout /= 100.0;
		PWM_APP = Uout;
		PWM_REL = 0;
		if(Uout > 0 && Uout < 0.3)
			PWM_APP = 0.25;
		if(Uout > 1)
			PWM_APP = 1;

	}
	else 
	{
		PWM_APP = 0;
		PWM_REL = 0.23;
	}



}
//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CAN0_ISR
//-----------------------------------------------------------------------------
INTERRUPT (CAN0_ISR, INTERRUPT_CAN0)
{
   U8 carry;
   UU32 new_data;

   // SFRPAGE is set to CAN0_Page automatically when ISR starts

   U8 status = CAN0STAT;               // Read status, which clears the Status
                                       // Interrupt bit pending in CAN0IID

   U8 Interrupt_ID = CAN0IID;          // Read which message object caused
                                       // the interrupt
   // The CAN0ND registers tell which of the 32 message objects are new.
   // Read data from CAN registers and perform 1-bit right shift with carry
   new_data.U8[b0] = CAN0ND1L;         // With a big endian compiler, assign LSB
   new_data.U8[b1] = CAN0ND1H;
   new_data.U8[b2] = CAN0ND2L;
   new_data.U8[b3] = CAN0ND2H;         // Assign MSB
   carry = new_data.U8[b0] & 0x01;     // Store carry bit
   new_data.U32 = new_data.U32 >> 1;   // Perform 1-bit shift to realign

   if (carry)
   { // Add carry if necessary
      new_data.U8[b3] = new_data.U8[b3] | 0x80;
   }

   // new_data variable will now tell which message object is new.

   CAN0IF1CM = 0x007F;                 // Read all of message object to IF1
                                       // Clear IntPnd and newData

   CAN0IF1CR = Interrupt_ID;           // Start command request

   while (CAN0IF1CRH & 0x80) {}           // Poll on Busy bit

   if (status & RxOk )                  // If transmit completed successfully
   {
       // Read all 8 data bytes to rxdata, even though they might not be valid
      CAN_Rx_Buf[0] = CAN0IF1DA1L;
      CAN_Rx_Buf[1] = CAN0IF1DA1H;
      CAN_Rx_Buf[2] = CAN0IF1DA2L;
      CAN_Rx_Buf[3] = CAN0IF1DA2H;
      CAN_Rx_Buf[4] = CAN0IF1DB1L;
      CAN_Rx_Buf[5] = CAN0IF1DB1H;
      CAN_Rx_Buf[6] = CAN0IF1DB2L;
      CAN_Rx_Buf[7] = CAN0IF1DB2H;
      CAN_RX_COMPLETE = 1;
	
	if(Interrupt_ID == Broadcast_ID  && CAN_Rx_Buf[3] == IPM_ID)
	{
		if( CAN_Rx_Buf[1] == 0x01)
		{
			switch(CAN_Rx_Buf[0])
			{
				case 0x01: Yunzhuanwei(); break;
				case 0x02: Chuzhiwei(); break;
				case 0x04: Quanzhidongwei(); break;
				case 0x08: Yizhiwei(); break;
				case 0x10: Chonglianwei(); break;
				case 0x20: Jinjiwei(); break;
				default:break;
			}
	
			CAN_Tx_Buf[0] = CAN_Rx_Buf[0];
			CAN_Tx_Buf[1] = CAN_Rx_Buf[1];
			CAN_Tx_Buf[3] = ERCP_ID;
			CAN_Tx_Buf[4] = FaultCode;
			CAN0_TransferMO(IPM_ID);
			CAN0_TransferMO(BPCP_ID);
		}
	}
   }
   // If an error occured, simply update the global variable and continue
   if (status & LEC)
   {
       // The LEC bits identify the type of error, but those are grouped here
       if ((status & LEC) != 0x07)
       {
          CAN_ERROR = 1;
       }
   }

   if (status & BOff)
   {
      CAN_ERROR = 1;
   }

   if (status & EWarn)
   {
      CAN_ERROR = 1;
   }

   // Old SFRPAGE is popped off stack when ISR exits
}
INTERRUPT (TIMER0_ISR, INTERRUPT_TIMER0)
{
	TF0 = 0;
	TL0       = 0x90;	
  TH0       = 0xE8;			//3ms,based on 2MHz clock 

	PIDControl();
	
}
INTERRUPT (TIMER2_ISR, INTERRUPT_TIMER2)
{

//	DisplayNumber(2);
   TF2H = 0;                           // Reset Interrupt
      // Set up the AMUX for the next ADC input
   if (AMUX_INPUT == (ANALOG_INPUTS - 1))
   {
      ADC0MX = PIN_TABLE[0] | 0x10;
   }
   else
   {
      ADC0MX = PIN_TABLE[AMUX_INPUT+1] | 0x10;
   }
   //SendMessageCAN0(EPCU_ERCP_MO,g_uTx_Data1);
   
}


INTERRUPT (TIMER3_ISR, INTERRUPT_TIMER3)
{
	TMR3CN &= 0x7F;//clear flag

	PWM_APP *= 100;
	PWM_REL *= 100;

	PWM_Count++;

	if(PWM_Count > PWM_Period)
		PWM_Count = 0;

	if(PWM_Count < PWM_APP)
		APP_ON;
	else 
		APP_OFF;

	if(PWM_Count < PWM_REL)
		REL_ON;
	else
		REL_OFF;

}


INTERRUPT (ADC0_ISR, INTERRUPT_ADC0_EOC)
{
   static U16 int_dec = INT_DEC;       // Integrate/decimate counter
                                       // A new result is posted when
                                       // int_dec is 0
	
   U8 i;                               // Loop counter


   AD0INT = 0;                         // Clear ADC conversion complete
                                       // overflow


   accumulator[AMUX_INPUT] += ADC0;    // Read the ADC value and add it to the
                                       // running total

   // Reset sample counter <int_dec> and <AMUX_INPUT> if the final input was
   // just read
   if(AMUX_INPUT == (ANALOG_INPUTS - 1))
   {
      int_dec--;                       // Update decimation counter
                                       // when the last of the analog inputs
                                       // is sampled

      if (int_dec == 0)                // If zero, then post the averaged
      {                                // results
         int_dec = INT_DEC;            // Reset counter

         // Copy each averaged ADC0 value into the RESULT array
         for(i = 0; i < ANALOG_INPUTS; i++)
         {
            // Copy averaged values into RESULT
            RESULT[i] = accumulator[i] / int_dec;

            // Reset accumulators
            accumulator[i] = 0x00000000;
         }
      }

      AMUX_INPUT = 0;                  // Reset input index back to P0.1
   }
   // Otherwise, increment the AMUX channel counter
   else
   {
      AMUX_INPUT++;                    // Step to the next analog mux input
   }
	 //smg_display(0xe,0xa,0xc,18);
}





void Yunzhuanwei()
{
	RelayON;
	APP_ON;
	REL_OFF;
}
void Chuzhiwei()
{
	Target_ERT_Pressure = 50;
	RelayON;
}

void Quanzhidongwei()
{
	RelayON;
	Target_ERT_Pressure = 170;
}

void Yizhiwei()
{
	RelayON;
	Target_ERT_Pressure = 170;
}

void Chonglianwei()
{
	RelayON;
	Target_ERT_Pressure = 0;
}

void Jinjiwei()
{
	RelayON;
	Target_ERT_Pressure = 0;
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------