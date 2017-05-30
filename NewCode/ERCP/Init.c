
#include "Init.h"
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
	ADC0L = 0x48;
	ADC0H = 0x07;
	ADC0L = 0xd0;
	ADC0H = 0x08;
	ADC0L = 0x01;
	ADC0CF &= ~0x01;

	ADC0CN = 0x10;           //0 start by writing 1 to AD0BUSY, 1 start by overflow of timer 1 , 3 by timer 2

	REF0CN = 0x03;

	ADC0MX = 0x10| PIN_TABLE[AMUX_INPUT];

	ADC0CF = ((SYSCLK /3000000) - 1) << 3;

	EIE1 |= 0x04;

	AD0EN = 1;

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
   TH0       = 0xE8;			//3ms,based on 2MHz clock        		℅“車?車迆??DD?D?車那??邦芍?3ms?“那㊣
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
    TMR3H     = 0xF8;			//    車?車迆S㏒?ms?“那㊣ */
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




