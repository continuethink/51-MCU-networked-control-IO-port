#include <REGX52.H>

void Uart_Init()
{
	PCON&=0X3F;
	SCON=0X50;
	EA=1;
	ES=1;
	TMOD&=0X0F;
	TMOD|=0X20;
	TH1=0XFD;
	TL1=0XFD;
	ET1=0;
	TR1=1;
}

void Uart_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

void Uart_SendFile(unsigned char *file)
{
	while(*file!='\0')
	{
		Uart_SendByte(*file);
		file++;
	}
}