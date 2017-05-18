//-----------------------------------------------------------------------------
// C8051F500_defs.h
//-----------------------------------------------------------------------------
// Copyright 2009, Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// Register/bit definitions for the C8051F50x family.
// **Important Note**: The compiler_defs.h header file should be included
// before including this header file.
//
// Target:         C8051F500/1/2/3/4/5/6/7/8/9-F510/1
// Tool chain:     Generic
// Command Line:   None
//
// Release 0.6 - 01 APR 2009 (GP)
//    -Added SN0-SN3
//
// Release 0.5 - 16 FEB 2009 (GP)
//    -Updated part numbers
//
// Release 0.4 - 17 JUL 2008 (GP)
//    -Fixed SCON0 and TMR2CN bit defintions
//
// Release 0.3 - 09 JUL 2008 (GP)
//    -Initial release
//

//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------

#ifndef C8051F500_DEFS_H
#define C8051F500_DEFS_H

//-----------------------------------------------------------------------------
// Page 0 and Page F Registers
//-----------------------------------------------------------------------------

sfr P0       = 0x80;    /* PORT 0                                       */	
sfr SP       = 0x81;    /* STACK POINTER                                */
sfr DPL      = 0x82;    /* DATA POINTER - LOW BYTE                      */
sfr DPH      = 0x83;    /* DATA POINTER - HIGH BYTE                     */
sfr SFR0CN   = 0x84;    /* SFR PAGE SELECT                              */
sfr SFRNEXT  = 0x85;    /* SFR STACK NEXT PAGE                          */
sfr SFRLAST  = 0x86;    /* SFR STACK LAST PAGE                          */
sfr PCON     = 0x87;    /* POWER CONTROL                                */
sfr TCON     = 0x88;    /* TIMER CONTROL                                */
sfr TMOD     = 0x89;    /* TIMER MODE                                   */
sfr TL0      = 0x8A;    /* TIMER 0 - LOW BYTE                           */
sfr TL1      = 0x8B;    /* TIMER 1 - LOW BYTE                           */
sfr TH0      = 0x8C;    /* TIMER 0 - HIGH BYTE                          */
sfr TH1      = 0x8D;    /* TIMER 1 - HIGH BYTE                          */
sfr CKCON    = 0x8E;    /* TIMER 0/1 CLOCK CONTROL                      */
sfr PSCTL    = 0x8F;    /* FLASH WRITE/ERASE CONTROL                    */
sfr CLKSEL   = 0x8f;    /* System clock select                          */
sfr P1       = 0x90;    /* PORT 1                                       */
sfr TMR3CN   = 0x91;    /* Timer counter 3 control                      */
sfr TMR3RLL  = 0x92;    //timer counter 3 reload low
sfr TMR3RLH  = 0x93;    //timer counter 3 reload high
sfr TMR3L    = 0x94;    //timer counter 3 low
sfr TMR3H    = 0x95;    //timer counter 3 high
sfr CLKMUL   = 0x97;    /* SYSTEM CLOCK SELECT                          */
sfr SCON0    = 0x98;    /* UART 0 CONTROL                               */
sfr SBUF0    = 0x99;    /* UART 0 BUFFER                                */
sfr CPT0CN   = 0x9a;    //comparator 0 control
sfr CPT0MD   = 0x9b;    //comparator 0 mode
sfr CPT0MX   = 0x9c;    //comparator 0 mux
sfr CPT1CN   = 0x9d;    //comparator 1 control
sfr CPT1MD   = 0x9e;    //comparator 1 mode
sfr OSCIFIN  = 0x9e;    //internal oscillator fine control
sfr CPT1MX   = 0x9f;    //comparator 1 mux
sfr OSCXCN   = 0x9f;    // External Oscillator Control
sfr P2       = 0xa0;    //port 2 latch
sfr SPI0CFG  = 0xa1;    //spi0 configuration
sfr OSCICN   = 0xa1;    // Internal Oscillator Control
sfr OSCICKR  = 0xa2;    // SPI0 clock rate control
sfr OSCICRS  = 0xa2;    //Internal oscillator coarse control
sfr SPI0DAT  = 0xa3;    //SPI0 data buffer
sfr P0MDOUT  = 0xa4;    // Port 0 Output Mode
sfr P1MDOUT  = 0xa5;    //Port  1 Output Mode
sfr P2MDOUT  = 0xa6;    //port 2 output mode
sfr SFRPAGE  = 0xa7;    //sfr page select
sfr IE       = 0xa8;    //interrupt enable
sfr SMOD0    = 0xa9;    //serial port0 control
sfr EMI0CN   = 0xaa;    //EMIF control
sfr EMI0TC   = 0xaa;    //EMIF timing control
sfr SBCON0   = 0xab;    //uart0 baud rate generator control
sfr SBRLL0   = 0xac;    //uart0 baud rate generator low
sfr SBRLH0   = 0xad;    //uart0 baud rate generator high
sfr P3MAT    = 0xae;    //port 3 match 
sfr P3MDOUT  = 0xae;    //port 3 mode
sfr P3MASK   = 0xaf;    //port 3 mask
sfr P4MDOUT  = 0xaf;    //port 4 mode
sfr P3       = 0xb0;    //port 3 latch
sfr P2MAT    = 0xb1;    //port 2 match 
sfr P2MASK   = 0xb2;    //port 2 mask
sfr EMI0CF   = 0xb2;    //EMIF configuration
sfr P4       = 0xb5;    //port 4 latch
sfr FLSCL    = 0xb6;    //flash scale
sfr FLKEY    = 0xb7;    //flash access limit
sfr IP       = 0xb8;    //interrupt priority
sfr SMB0ADR  = 0xb9;    // SMBus0 Slave address
sfr ADC0TK   = 0xba;    //adc0 tracking mode select
sfr SMB0ADM  = 0xba;    //smbus0 address mask
sfr ADC0MX   = 0xbb;    // AMUX0 Channel select
sfr ADC0CF   = 0xbc;    // AMUX0 Channel configuration
sfr ADC0L    = 0xbd;    // ADC0 Data Low
sfr ADC0H    = 0xbe;    // ADC0 Data High
sfr SMB0CN   = 0xc0;    // SMBus0 Control
sfr SMB0CF   = 0xc1;    // SMBus0 Configuration
sfr SMB0DAT  = 0xc2;    // SMBus0 Data
sfr ADC0GTL  = 0xc3;    // ADC0 Greater-Than Compare Low
sfr ADC0GTH  = 0xc4;    // ADC0 Greater-Than Compare High
sfr ADC0LTL  = 0xc5;    // ADC0 Less-Than Compare Word Low
sfr ADC0LTH  = 0xc6;    // ADC0 Less-Than Compare Word High
sfr XBR2     = 0xc7;    // Port I/O Crossbar Control 2
sfr TMR2CN   = 0xc8;    // Timer/Counter 2 Control
sfr REG0CN   = 0xc9;    // Regulator Control
sfr LIN0CF   = 0xc9;    // LIN 0 Configuration
sfr TMR2RLL  = 0xca;    // Timer/Counter 2 Reload Low
sfr TMR2RLH  = 0xcb;    // Timer/Counter 2 Reload High
sfr TMR2L    = 0xcc;    // Timer/Counter 2 Low
sfr TMR2H    = 0xcd;    // Timer/Counter 2 High
sfr PCA0CPL5 = 0xce;    // PCA0 Capture 5 Low
sfr PCA0CPH5 = 0xcf;    // PCA0 Capture 5 High
sfr PSW      = 0xd0;     // Program Status Word
sfr REF0CN   = 0xd1;   // Voltage Reference Control
sfr LIN0DAT  = 0xd2;     // LIN0 Data
sfr LIN0ADR  = 0xd3;    // LIN0 Address
sfr P0SKIP   = 0xd4;    // Port 0 Skip
sfr P1SKIP   = 0xd5;     // Port 1 Skip
sfr P2SKIP   = 0xd6;       // Port 2 Skip
sfr P3SKIP   = 0xd7;      // Port 3 Skip
sfr PCA0CN   = 0xd8;       // PCA0 Control
sfr PCA0MD   = 0xd9;         // PCA0 Mode
sfr PCA0PWM  = 0xd9;         // PCA0 PWM Control
sfr PCA0CPM0 = 0xda;       // PCA0 Module 0 Mode Register
sfr PCA0CPM1 = 0xdb;          // PCA0 Module 1 Mode Register
sfr PCA0CPM2 = 0xdc;      // PCA0 Module 2 Mode Register
sfr PCA0CPM3 = 0xdd;        // PCA0 Module 3 Mode Register  
sfr PCA0CPM4 = 0xde;   // PCA0 Module 4 Mode Register
sfr PCA0CPM5 = 0xdf;                  // PCA0 Module 5 Mode Register
sfr ACC      = 0xe0;       // Accumulator
sfr XBR0     = 0xe1;    // Port I/O Crossbar Control 0
sfr XBR1     = 0xe2;   // Port I/O Crossbar Control 1
sfr CCH0CN   = 0xe3;       // Cache control
sfr IT01CF   = 0xe4;     // INT0/INT1 Configuration
sfr EIE1     = 0xe6;        // Extended Interrupt Enable 2
sfr EIE2     = 0xe7;       // Extended Interrupt Enable 2
sfr ADC0CN   = 0xe8;      // ADC0 Control
sfr PCA0CPL1 = 0xe9;   // PCA0 Capture 2 Low
sfr PCA0CPH1 = 0xea;     // PCA0 Capture 2 High
sfr PCA0CPL2 = 0xeb;     // PCA0 Capture 3 Low
sfr PCA0CPH2 = 0xec;       // PCA0 Capture 3 High
sfr PCA0CPL3 = 0xed;      // PCA0 Capture 4 Low
sfr PCA0CPH3 = 0xee;     // PCA0 Capture 4 High
sfr RSTSRC   = 0xef;     // Reset Source Configuration/Status
sfr B        = 0xf0;     // B Register
sfr P0MAT    = 0xf1;       // Port 0 Match
sfr P0MDIN   = 0xf1;        // Port 0 Input Mode
sfr P0MASK   = 0xf2;       // Port 0 Mask
sfr P1MDIN   = 0xf2;      // Port 1 Input Mode
sfr P1MAT    = 0xf3 ;     // Port 1 Match
sfr P2MDIN   = 0xf3;     // Port 2 Input Mode  
sfr P1MASK   = 0xf4;    // Port 1 Mask
sfr P3MDIN   = 0xf4;       // Port 3 Input Mode
sfr EIP1     = 0xf6;      // External Interrupt Priority 1
sfr EIP2     = 0xf7;        // External Interrupt Priority 2
sfr SPI0CN   = 0xf8;        // SPI0 Control
sfr PCA0L    = 0xf9;     // PCA0 Counter Low
sfr SN0      = 0xf9;        // Serial Number 0
sfr PCA0H    = 0xfa;     // PCA0 Counter High
sfr SN1      = 0xfa;      // Serial Number 1
sfr PCA0CPL0 = 0xfb;     // PCA0 Capture 0 Low
sfr SN2      = 0xfb;    // Serial Number 2
sfr PCA0CPH0 = 0xfc;      // PCA0 Capture 0 High
sfr SN3      = 0xfc;      // Serial Number 3
sfr PCA0CPL4 = 0xfd;     // PCA0 Capture 4 Low
sfr PCA0CPH4 = 0xfe;   // PCA0 Capture 4 High
sfr VDM0CN   = 0xff;       // VDD Monitor Control

//-----------------------------------------------------------------------------
// Page C (CAN0) Registers
//-----------------------------------------------------------------------------

sfr CAN0CFG     = 0x92;  // CAN0 Clock Configuration
sfr CAN0STAT    = 0x94;    // Status Register Low Byte
sfr CAN0ERRL    = 0x96;                  // Error Counter Low Byte
sfr CAN0ERRH    = 0x97;              // Error Counter High Byte
sfr CAN0BTL     = 0x9a;              // Bit Timing Register Low Byte
sfr CAN0BTH     = 0x9b;            // Bit Timing Register High Byte
sfr CAN0IIDL    = 0x9c;    // Interrupt Register Low Byte
sfr CAN0IIDH    = 0x9d;           // Interrupt Register High Byte
sfr CAN0TST     = 0x9e;            // Test Register Low Byte
sfr CAN0BRPE    = 0xa1;         // BRP Extension Register Low Byte
sfr CAN0TR1L    = 0xa2;              // Transmission Request 1 Low Byte
sfr CAN0TR1H    = 0xa3;             // Transmission Request 1 High Byte
sfr CAN0TR2L    = 0xa4;           // Transmission Request 2 Low Byte
sfr CAN0TR2H    = 0XA5;               // Transmission Request 2 High Byte
sfr CAN0ND1L    = 0XAA;             // New Data 1 Low Byte
sfr CAN0ND1H    = 0XAB;              // New Data 1 High Byte
sfr CAN0ND2L    = 0XAC;           // New Data 2 Low Byte
sfr CAN0ND2H    = 0XAD;           // New Data 2 High Byte
sfr CAN0IP1L    = 0XAE;         // Interrupt Pending 1 Low Byte
sfr CAN0IP1H    = 0XAF;           // Interrupt Pending 1 High Byte
sfr CAN0IP2L    = 0XB2;            // Interrupt Pending 2 Low Byte
sfr CAN0IP2H    = 0XB3;         // Interrupt Pending 2 High Byte
sfr CAN0MV1L    = 0XBA;          // Message Valid 1 Low Byte
sfr CAN0MV1H    = 0XBB;             // Message Valid 1 High Byte
sfr CAN0MV2L    = 0XBC;      // Message Valid 2 Low Byte
sfr CAN0MV2H    = 0XBD;         // Message Valid 2 High Byte
sfr CAN0IF1CRL  = 0XBE;        // IF1 Command Request Low Byte
sfr CAN0IF1CRH  = 0XBF;       // IF1 Command Request High Byte
sfr CAN0CN      = 0XC0;            // CAN Control Register Low Byte
sfr CAN0IF1CML  = 0XC2;
sfr CAN0IF1CMH  = 0XC3;
sfr CAN0IF1M1L  = 0XC4;
sfr CAN0IF1M1H  = 0XC5;
sfr CAN0IF1M2L  = 0XC6;
sfr CAN0IF1M2H  = 0XC7;
sfr CAN0IF1A1L  = 0XCA;
sfr CAN0IF1A1H  = 0XCB;
sfr CAN0IF1A2L  = 0XCC;
sfr CAN0IF1A2H  = 0XCD;
sfr CAN0IF2MCL  = 0XCE;
sfr CAN0IF2MCH  = 0XCF;
sfr CAN0IF1MCL  = 0XD2;
sfr CAN0IF1MCH  = 0XD3;
sfr CAN0IF1DA1L = 0XD4;
sfr CAN0IF1DA1H = 0XD5;
sfr CAN0IF1DA2L = 0XD6;
sfr CAN0IF1DA2H = 0XD7;
sfr CAN0IF1DB1L = 0XDA;
sfr CAN0IF1DB1H = 0XDB;
sfr CAN0IF1DB2L = 0XDC;
sfr CAN0IF1DB2H = 0XDD;
sfr CAN0IF2CRL  = 0XDE;
sfr CAN0IF2CRH  = 0XDF;
sfr CAN0IF2CML  = 0XE2;
sfr CAN0IF2CMH  = 0XE3;
sfr CAN0IF2M1L  = 0XEA;
sfr CAN0IF2M1H  = 0XEB;
sfr CAN0IF2M2L  = 0XEC;
sfr CAN0IF2M2H  = 0XED;
sfr CAN0IF2A1L  = 0XEE;
sfr CAN0IF2A1H  = 0XEF;
sfr CAN0IF2A2L  = 0XF2;
sfr CANIF2A2H   = 0XF3;
sfr CAN0IF2DA1L = 0XF6;
sfr CAN0IF2DA1H = 0XF7;
sfr CAN0IF2DA2L = 0XFA;
sfr CAN0IF2DA2H = 0XFB;
sfr CAN0IF2DB1L = 0XFC;
sfr CAN0IF2DB1H = 0XFD;
sfr CAN0IF2DB2L = 0XFE;
sfr CAN0IF2DB2H = 0XFF;

//-----------------------------------------------------------------------------
// 16-bit Register Definitions (might not be supported by all compilers)
//-----------------------------------------------------------------------------
sfr16 DP      = 0X82;
sfr16 TMR3RL  = 0X92;
sfr16 TMR3    = 0X94;
sfr16 SBRL0   = 0XAC;
sfr16 ADC0    = 0XBD;
sfr16 ADC0GT  = 0XC3;
sfr16 ADC0LT  = 0XC5;
sfr16 TMR2RL  = 0XCA;
sfr16 TMR2    = 0XCC;
sfr16 PCA0CP5 = 0XCE;
sfr16 PCA0CP1 = 0XE9;
sfr16 PCA0CP2 = 0XEB;
sfr16 PCA0CP3 = 0XED;
sfr16 PCA0    = 0XF9;
sfr16 PCA0CP0 = 0XFB;
sfr16 PCA0CP4 = 0XFD;

sfr16 CAN0ERR = 0X96;
sfr16 CAN0BT  = 0X9A;
sfr16 CAN0IID = 0X9C;
sfr16 CAN0TR1 = 0XA2;
sfr16 CAN0TR2 = 0XA4;
sfr16 CAN0ND1 = 0XAA;
sfr16 CAN0ND2 = 0XAC;
sfr16 CAN0IP1 = 0XAE;
sfr16 CAN0IP2 = 0XB2;
sfr16 CAN0MV1 = 0XBA;
sfr16 CAN0MV2 = 0XBC;
sfr16 CAN0IF1CR = 0XBE;
sfr16 CAN0IF1CM = 0XC2;
sfr16 CAN0IF1M1 = 0XC4;
sfr16 CAN0IF1M2 = 0XC6;
sfr16 CAN0IF1A1 = 0XCA;
sfr16 CAN0IF1A2 = 0XCC;
sfr16 CAN0IF2MC = 0XCE;
sfr16 CAN0IF1MC = 0XD2;
sfr16 CAN0IF1DA1 = 0XD4;
sfr16 CAN0IF1DA2 = 0XD6;
sfr16 CAN0IF1DB1 = 0XDA;
sfr16 CAN0IF1DB2 = 0XDC;
sfr16 CAN0IF2CR  = 0XDE;
sfr16 CAN0IF2CM  = 0XE2;
sfr16 CAN0IF2M1  = 0XEA;
sfr16 CAN0IF2M2 = 0XEC;
sfr16 CAN0IF2A1  = 0XEE;
sfr16 CAN0IF2A2  = 0XF2;
sfr16 CAN0IF2DA1 = 0XF6;
sfr16 CAN0IF2DA2 = 0XFA;
sfr16 CAN0IF2DB1 = 0XFC;
sfr16 CAN0IF2DB2 = 0XFE;

//-----------------------------------------------------------------------------
// LIN0 Indirect Registers
//-----------------------------------------------------------------------------

#define  LIN0DT1   0x00                // LIN0 Data Byte 1
#define  LIN0DT2   0x01                // LIN0 Data Byte 2
#define  LIN0DT3   0x02                // LIN0 Data Byte 3
#define  LIN0DT4   0x03                // LIN0 Data Byte 4
#define  LIN0DT5   0x04                // LIN0 Data Byte 5
#define  LIN0DT6   0x05                // LIN0 Data Byte 6
#define  LIN0DT7   0x06                // LIN0 Data Byte 7
#define  LIN0DT8   0x07                // LIN0 Data Byte 8
#define  LIN0CTRL  0x08                // LIN0 Control
#define  LIN0ST    0x09                // LIN0 Status
#define  LIN0ERR   0x0A                // LIN0 Error
#define  LIN0SIZE  0x0B                // LIN0 Message Size
#define  LIN0DIV   0x0C                // LIN0 Divider
#define  LIN0MUL   0x0D                // LIN0 Multiplier
#define  LIN0ID    0x0E                // LIN0 Identifier

//-----------------------------------------------------------------------------
// Address Definitions for Bit-addressable Registers
//-----------------------------------------------------------------------------

#define SFR_P0       0x80
#define SFR_TCON     0x88
#define SFR_P1       0x90
#define SFR_SCON0    0x98
#define SFR_P2       0xA0
#define SFR_IE       0xA8
#define SFR_P3       0xB0
#define SFR_IP       0xB8
#define SFR_SMB0CN   0xC0
#define SFR_TMR2CN   0xC8
#define SFR_PSW      0xD0
#define SFR_PCA0CN   0xD8
#define SFR_ACC      0xE0
#define SFR_ADC0CN   0xE8
#define SFR_B        0xF0
#define SFR_SPI0CN   0xF8

//-----------------------------------------------------------------------------
// Bit Definitions
//-----------------------------------------------------------------------------

// TCON 0x88
sbit TF1   = TCON ^ 7;              /* TIMER 1 OVERFLOW FLAG      */
sbit TR1   = TCON ^ 6;              /* TIMER 1 ON/OFF CONTROL     */
sbit TF0   = TCON ^ 5;              /* TIMER 0 OVERFLOW FLAG      */
sbit TR0   = TCON ^ 4;              /* TIMER 0 ON/OFF CONTROL     */
sbit IE1   = TCON ^ 3;              /* EXT. INTERRUPT 1 EDGE FLAG */
sbit IT1   = TCON ^ 2;              /* EXT. INTERRUPT 1 TYPE      */
sbit IE0   = TCON ^ 1;              /* EXT. INTERRUPT 0 EDGE FLAG */
sbit IT0   = TCON ^ 0;              /* EXT. INTERRUPT 0 TYPE      */

// SCON0 0x98
sbit OVER0  = SCON0 ^ 7;           // UART0 Mode 0
sbit PERR0  = SCON0 ^ 6;           // UART0 Parity Error Flag
sbit THRE0  = SCON0 ^ 5;           // UART0 Transmit Holding Reg. Empty
sbit REN0   = SCON0 ^ 4;          // UART0 RX Enable
sbit TBX0   = SCON0 ^ 3;           // UART0 TX Bit 8
sbit RBX0   = SCON0 ^ 2;         // UART0 RX Bit 8
sbit TI0    = SCON0 ^ 1;         // UART0 TX Interrupt Flag
sbit RI0    = SCON0 ^ 0;        // UART0 RX Interrupt Flag
   

// IE 0xA8
sbit EA    = IE ^ 7;                /* GLOBAL INTERRUPT ENABLE      */	
sbit ESPI0 = IE ^ 6;                // SPI0 Interrupt Enable
sbit ET2   = IE ^ 5;                /* TIMER 2 INTERRUPT ENABLE     */
sbit ES0   = IE ^ 4;                /* UART0 INTERRUPT ENABLE       */
sbit ET1   = IE ^ 3;                /* TIMER 1 INTERRUPT ENABLE     */
sbit EX1   = IE ^ 2;                /* EXTERNAL INTERRUPT 1 ENABLE  */
sbit ET0   = IE ^ 1;                /* TIMER 0 INTERRUPT ENABLE     */
sbit EX0   = IE ^ 0;                /* EXTERNAL INTERRUPT 0 ENABLE  */
// IP 0xB8
                                       // Bit 7 unused
sbit PSPI0 = IP ^ 6;               // SPI0 Interrupt Priority
sbit PT2   = IP ^ 5;                /* TIMER 2 PRIORITY					*/	
sbit PS    = IP ^ 4;                /* SERIAL PORT PRIORITY				*/
sbit PT1   = IP ^ 3;                /* TIMER 1 PRIORITY					*/
sbit PX1   = IP ^ 2;                /* EXTERNAL INTERRUPT 1 PRIORITY	*/
sbit PT0   = IP ^ 1;                /* TIMER 0 PRIORITY					*/
sbit PX0   = IP ^ 0;                /* EXTERNAL INTERRUPT 0 PRIORITY	*/

// SMB0CN 0xC0
sbit MASTER  = SMB0CN ^ 7;          // SMBus0 Master/Slave Indicator
sbit TXMODE  = SMB0CN ^ 6;         // SMBus0 Master/Slave Indicator
sbit STA     = SMB0CN ^ 5;         // SMBus0 Start Flag
sbit STO     = SMB0CN ^ 4;         // SMBus0 Stop Flag
sbit ACKRQ   = SMB0CN ^ 3;       // SMBus0 Acknowledge Request
sbit ARBLOST = SMB0CN ^ 2;       // SMBus0 Arbitration Lost Indicator
sbit ACK     = SMB0CN ^ 1;        // SMBus0 Acknowledge
sbit SI      = SMB0CN ^ 0;            // SMBus0 Interrupt Flag

// TMR2CN 0xC8
sbit TF2H    = TMR2CN ^ 7;            // Timer 2 High-Byte Overflow Flag
sbit TF2L    = TMR2CN ^ 6;            // Timer 2 Low-Byte  Overflow Flag
sbit TE2LEN  = TMR2CN ^ 5;            // Timer 2 Low-Byte Flag Enable
sbit TF2CEN  = TMR2CN ^ 4;            // Timer 2 Capture Enable
sbit T2SPLIT = TMR2CN ^ 3;            /* Timer 2 Split-Mode Enable*/	
sbit TR2     = TMR2CN ^ 2;            /* Timer2 Run Enable       */
 
sbit T2XCLK  = TMR2CN ^ 0;            /* Timer 2 Clk/8 Clock Source*/

// PSW 0xD0
sbit CY  = PSW ^ 7;                 /* CARRY FLAG              */	
sbit AC  = PSW ^ 6;                 /* AUXILIARY CARRY FLAG    */
sbit F0  = PSW ^ 5;                 /* USER FLAG 0             */
sbit RS1 = PSW ^ 4;                 /* REGISTER BANK SELECT 1  */
sbit RS0 = PSW ^ 3;                 /* REGISTER BANK SELECT 0  */
sbit OV  = PSW ^ 2;                 /* OVERFLOW FLAG           */
sbit F1  = PSW ^ 1;                 /* USER FLAG 1             */
sbit P   = PSW ^ 0;                 /* ACCUMULATOR PARITY FLAG */

// PCA0CN 0xD8
sbit CF   = PCA0CN ^ 7;             /* PCA 0 COUNTER OVERFLOW FLAG   */
sbit CR   = PCA0CN ^ 6;             /* PCA 0 COUNTER RUN CONTROL BIT */
sbit CCF5 = PCA0CN ^ 5;             /* PCA 0 MODULE 5 INTERRUPT FLAG */
sbit CCF4 = PCA0CN ^ 4;             /* PCA 0 MODULE 4 INTERRUPT FLAG */
sbit CCF3 = PCA0CN ^ 3;             /* PCA 0 MODULE 3 INTERRUPT FLAG */
sbit CCF2 = PCA0CN ^ 2;             /* PCA 0 MODULE 2 INTERRUPT FLAG */
sbit CCF1 = PCA0CN ^ 1;             /* PCA 0 MODULE 1 INTERRUPT FLAG */
sbit CCF0 = PCA0CN ^ 0;             /* PCA 0 MODULE 0 INTERRUPT FLAG */

// ADC0CN 0xE8
sbit AD0EN   = ADC0CN ^ 7;          /* ADC 0 ENABLE                   */
sbit BURSTEN = ADC0CN ^ 6;          /* ADC 0 Burst Enable               */
sbit AD0INT  = ADC0CN ^ 5;          /* ADC 0 EOC INTERRUPT FLAG       */
sbit AD0BUSY = ADC0CN ^ 4;          /* ADC 0 BUSY FLAG                */
sbit AD0WINT = ADC0CN ^ 3;          /* ADC0 Window Compare Interrupt Flag */
sbit AD0LJST = ADC0CN ^ 2;          /* ADC0 Left Justified */
sbit AD0CM1  = ADC0CN ^ 1;          /* ADC0 Start Of Conversion Mode Bit 1    */
sbit AD0CM0  = ADC0CN ^ 0;          // ADC0 Start Of Conversion Mode Bit 0

// SPI0CN 0xF8
sbit SPIF   = SPI0CN ^ 7;           /* SPI 0 INTERRUPT FLAG          */
sbit WCOL   = SPI0CN ^ 6;           /* SPI 0 WRITE COLLISION FLAG    */
sbit MODF   = SPI0CN ^ 5;           /* SPI 0 MODE FAULT FLAG         */
sbit RXOVRN = SPI0CN ^ 4;           /* SPI 0 RX OVERRUN FLAG         */
sbit NSSMD1 = SPI0CN ^ 3;			/* SPI 0 SLAVE SELECT MODE BIT 1 */
sbit NSSMD0 = SPI0CN ^ 2;			/* SPI 0 SLAVE SELECT MODE BIT 0 */
sbit TXBMT  = SPI0CN ^ 1;           /* SPI 0 TX BUFFER EMPTY         */
sbit SPIEN  = SPI0CN ^ 0;           /* SPI 0 SPI ENABLE              */	

//-----------------------------------------------------------------------------
// Interrupt Priorities
//-----------------------------------------------------------------------------

#define INTERRUPT_INT0             0   // External Interrupt 0
#define INTERRUPT_TIMER0           1   // Timer0 Overflow
#define INTERRUPT_INT1             2   // External Interrupt 1
#define INTERRUPT_TIMER1           3   // Timer1 Overflow
#define INTERRUPT_UART0            4   // UART0
#define INTERRUPT_TIMER2           5   // Timer2 Overflow
#define INTERRUPT_SPI0             6   // SPI0
#define INTERRUPT_SMBUS0           7   // SMBus0 Interface
#define INTERRUPT_ADC0_WINDOW      8   // ADC0 Window Comparison
#define INTERRUPT_ADC0_EOC         9   // ADC0 End Of Conversion
#define INTERRUPT_PCA0            10   // PCA0 Peripheral
#define INTERRUPT_COMPARATOR0     11   // Comparator0 Comparison
#define INTERRUPT_COMPARATOR1     12   // Comparator1 Comparison
#define INTERRUPT_TIMER3          13   // Timer3 Overflow
#define INTERRUPT_LIN0            14   // LIN Bus Interrupt
#define INTERRUPT_VREG            15   // Voltage Regulator
#define INTERRUPT_CAN0            16   // CAN Bus Interrupt
#define INTERRUPT_PORT_MATCH      17   // Port Match

//-----------------------------------------------------------------------------
// SFR Page Definitions
//-----------------------------------------------------------------------------

#define  CONFIG_PAGE       0x0F        // System and Port Configuration Page
#define  ACTIVE_PAGE       0x00        // Active Use Page
#define  CAN0_PAGE         0x0C        // CAN0 Registers

//-----------------------------------------------------------------------------
// Header File PreProcessor Directive
//-----------------------------------------------------------------------------

#endif                                 // #define C8051F500_DEFS_H

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------