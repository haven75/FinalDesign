//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "compiler_defs.h"
#include "C8051F500_defs.h"            // SFR declarations

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
void Timer2_Init(void);
void delay(U16 time);
void DisplayNumber(U16 i);
void CAN0_TransferMO (U8 obj_num);
void Yunzhuanwei(void);
void Chuzhiwei(void);
void Quanzhidongwei(void);
void Yizhiwei(void);
void Chonglianwei(void);
void Jinjiwei(void);
void Syunzhuanwei();
void Szhidongwei();
void Ceya();

INTERRUPT_PROTO (CAN0_ISR, INTERRUPT_CAN0);
INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define SYSCLK       24000000          // System clock speed in Hz

#define MESSAGE_OBJECTS    32          // Number of message objects to use
                                       // Range is 1-32
#define MESSAGE_SIZE        8          // Size in bytes of each CAN message
                                       // Range is 1-8

#define RX_COMPLETE_MASK  0xFFFFFFFF   // Set this to (2^MESSAGE_OBJECTS - 1)

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

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------

SBIT (LED, SFR_P1, 3);                 // LED = 1 turns on the LED

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
#define IPM_ID 0x001
#define EBV_ID 0x002
#define Broadcast_ID 0x003
#define ERCP_ID 0x010
#define BPCP_ID 0x011
#define CP16_ID 0x012
#define CP20_ID 0x013
#define CP13_ID 0x014
#define TIMER2_RELOAD  200000000
#define ANALOG_INPUTS    4
#define MVLT_ON (P1 &= ~0x40)
#define MVLT_OFF (P1 |= 0x40)
#define APP_ON ( P2 &= ~0x40)
#define APP_OFF (P2 |= 0x40)
#define REL_ON (P2 &= ~0x80)
#define REL_OFF (P2 |= 0x80)
//dispaly number define
U8 dis[10]={ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90 };
                   //   0    1    2    3    4    5    6    7    8    9 
bit CAN_ERROR = 0;                     // 0 = No Errors occurred
                                       // 1 = Some error(s) occurred
U8 FaultCode = 0x00 ;

U8 CAN_Tx_Buf[8] = {0xf1, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
U8 CAN_Rx_Buf[8];
U8 CAN_RX_COMPLETE;       
U8 Rx_Broadcast_OK = 0;           

U8 PIN_TABLE[ANALOG_INPUTS] = {0x00, 0x01, 0x02, 0x03};
U8 AMUX_INPUT = 0;

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
   Timer2_Init ();

   EIE2 |= 0x02;                       // Enable CAN interupts
   EA = 1;                             // Enable global interrupts
   P2 |= 0xC0;
   while (1)
   {
   		if(Rx_Broadcast_OK)
		{
			delay(50);
			CAN0_TransferMO(IPM_ID);
			Rx_Broadcast_OK = 0;
		}
   		DisplayNumber(20);
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

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

   P0MDOUT  |= 0x40;                   // P0.6 (CAN0 TX) is push-pull
   P1MDOUT  |= 0x08;                   // P1.3 (LED) is push-pull
   P1MDOUT &= 0xbf;          					//P1^6 open drain for relay
  // P2MDIN |= 0xf0;           					 //ADC
  // P2SKIP |= 0x0f;           					 //ADC
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
void ADC0_Init(void)
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = ACTIVE_PAGE;

	ADC0CF |= 0x01;
	ADC0H = 0x04;
	ADC0L = 0x6c;
	ADC0H = 0x07;
	ADC0L = 0xa0;
	ADC0H = 0x08;
	ADC0L = 0x01;
	ADC0CF &= ~0x01;

	ADC0CN = 0x10;           //0 start by writing 1 to AD0BUSY, 1 start by overflow of timer 1 , 3 by timer 2

	REF0CN = 0x33;

	ADC0MX = 0x10| PIN_TABLE[AMUX_INPUT];

	ADC0CF = ((SYSCLK /3000000) - 1) << 3;

//	EIE1 |= 0x04;

	AD0EN = 1;

	SFRPAGE = SFRPAGE_save;

}


//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
void Timer2_Init(void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   CKCON &= ~0x30;                     // Timer2 uses SYSCLK/12
   TMR2CN &= ~0x01;

   TMR2RL = TIMER2_RELOAD;             // Reload value to be used in Timer2
   TMR2 = TMR2RL;                      // Init the Timer2 register

   TMR2CN = 0x04;                      // Enable Timer2 in auto-reload mode
   ET2 = 1;                            // Timer2 interrupt enabled

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
   CAN0IF1A2 = 0xA000 | (IPM_ID << 2);  // Set MsgVal to valid
                                         // Set Direction to write
                                         // Set 11-bit Identifier to iter

   CAN0IF1CR = IPM_ID;                // Start command request

   while (CAN0IF1CRH & 0x80) {}       // Poll on Busy bit

   //---------Initialize settings for unused message objects

   for (iter = 0; iter < MESSAGE_OBJECTS; iter++)
   {
   	if(iter != Broadcast_ID && iter != IPM_ID)
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

	if(Interrupt_ID == Broadcast_ID && CAN_Rx_Buf[3] == IPM_ID)
	{	
		if( CAN_Rx_Buf[1] & 0x01 )
		{
		//	switch(CAN_Rx_Buf[0])
		//	{
		//		case 0x01: Yunzhuanwei(); break;
		//		case 0x02: Chuzhiwei(); break;
		//		case 0x04: Quanzhidongwei(); break;
		//		case 0x08: Yizhiwei(); break;
		//		case 0x10: Chonglianwei(); break;
		//		case 0x20: Jinjiwei(); break;
		//		default:break;
		//	}
			CAN_Tx_Buf[0] = CAN_Rx_Buf[0];
			CAN_Tx_Buf[1] = CAN_Rx_Buf[1];
			CAN_Tx_Buf[3] = CP20_ID;
			CAN_Tx_Buf[4] = FaultCode;
			Rx_Broadcast_OK = 1;
		}
		else if( CAN_Rx_Buf[1] == 0x02)
		{
			switch(CAN_Rx_Buf[0])
			{
				case 0x01: Syunzhuanwei();break;
				case 0x02: Szhidongwei();break;
				case 0x04: Ceya();break;
				default:break;
			}	
			CAN_Tx_Buf[0] = CAN_Rx_Buf[0];
			CAN_Tx_Buf[1] = CAN_Rx_Buf[1];
			CAN_Tx_Buf[3] = CP20_ID;
			CAN_Tx_Buf[4] = FaultCode;
	
			CAN0_TransferMO(IPM_ID);
		}

		else if (CAN_Rx_Buf[1] == 0x11)
		{

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

INTERRUPT (TIMER2_ISR, INTERRUPT_TIMER2)
{

//	DisplayNumber(2);
   TF2H = 0;                           // Reset Interrupt
   
}


//for delay time
void delay(U16 time)         //int型数据为16位,所以最大值为65535            
 {
  U16  i,j;             //定义变量i,j,用于循环语句 
  for(i=0;i<time;i++)    //for循环,循环50*time次
     for(j=0;j<100;j++); //for循环,循环50次
 }

 //display number
void DisplayNumber(U16 i)
{
	
	P3 |= dis[i/1000];
	P4 = 0x01;
	P4 = 0x00;
	P3 = 0x01;     //chose the thousand
	P4 = 0x02;
	P4 = 0x00;
	delay(10);
	P3 &= 0x00;



	P3 |= dis[(i%1000)/100];
	P4 = 0x01;
	P4 = 0x00;
	P3 = 0x02;
	P4 = 0x02;
	P4 = 0x00;
	delay(10);
	P3 = 0x00;




	P3 |= dis[(i%100) / 10];
	P4 = 0x01;
	P4 = 0x00;
	P3 = 0x04;
	P4 = 0x02;
	P4 = 0x00;
	delay(10);
	P3 &= 0x00;


	P3 = 0;
	P3 |= dis[i%10];
	P4 = 0x01;
	P4 = 0x00;
	P3 = 0x08;
	P4 = 0x02;
	P4 = 0x00;
	delay(10);
	P3 &= 0x00;
	

}

void Yunzhuanwei()
{

}
void Chuzhiwei()
{

}

void Quanzhidongwei()
{

}

void Yizhiwei()
{

}

void Chonglianwei()
{

}

void Jinjiwei()
{
	

}

void Syunzhuanwei()
{
	MVLT_ON;
	APP_OFF;
	REL_ON;
}

void Szhidongwei()
{
	MVLT_ON;
	APP_ON;
	REL_OFF;
}

void Ceya()
{
	MVLT_ON;
	APP_OFF;
	REL_OFF;
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

