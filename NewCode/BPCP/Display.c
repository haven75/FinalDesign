#include "Display.h"


 
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,//带小数点的0~9编码 
                     0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//带小数点的0~9编码

uchar code table1[]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,//带小数点的0~9编码 
                    0x88,0x83,0xc6,0xa1,0x86,0x8e, 0x89,0x88,0x8C,0xff}; //0x89 X 16
																	//0x88 R 17
																	//0x8C P 18




void delay_ms(uint x)
{
	int i,j;
	for(i=x;i>0;i--)
	for(j=100;j>0;j--);

}


void smg_display(uchar smg1_dat,uchar smg2_dat,uchar smg3_dat,uchar smg4_dat)
{
	Setwela(0);
	P3=0x00;
	delay_ms(1);
	Setwela(1);
	delay_ms(1);
	Setwela(0);

	Setdula(0); 
	P3=table1[smg1_dat];
	delay_ms(1);
	Setdula(1);	
	delay_ms(1);
    Setdula(0);
	
	Setwela(0);
	P3=0x01;
	delay_ms(1);
    Setwela(1);
	delay_ms(1);
	Setwela(0);

	delay_ms(10);




	Setwela(0);
	P3=0x00;
	delay_ms(1);
	Setwela(1);
	delay_ms(1);
	Setwela(0);



	Setdula(0); 
	P3=table1[smg2_dat];
	delay_ms(1);
	Setdula(1);	
	delay_ms(1);
    Setdula(0);
	
	Setwela(0);
	P3=0x02;
	delay_ms(1);
    Setwela(1);
	delay_ms(1);
	Setwela(0);
	Setwela(0);
	delay_ms(10);



	P3=0x00;
	delay_ms(1);
	Setwela(1);
	delay_ms(1);
	Setwela(0);

	Setdula(0); 
	P3=table1[smg3_dat];
	delay_ms(1);
	Setdula(1);	
	delay_ms(1);
    Setdula(0);

	Setwela(0);
	P3=0x04;
	delay_ms(1);
    Setwela(1);
	delay_ms(1);
	Setwela(0);




	delay_ms(10);

	P3=0x00;
	delay_ms(1);
	Setwela(1);
	delay_ms(1);
	Setwela(0);

	Setdula(0); 
	P3=table1[smg4_dat];
	delay_ms(1);
	Setdula(1);
	delay_ms(1);
    Setdula(0);

	Setwela(0);
	P3=0x08;
	delay_ms(1);
    Setwela(1);
	delay_ms(1);
	Setwela(0);
	delay_ms(10);
}
