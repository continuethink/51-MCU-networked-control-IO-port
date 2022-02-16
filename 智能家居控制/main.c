#include <REGX52.H>
#include "uart.h"
#include "delay.h"
#include "key.h"
#include "oled.h"
#include "bmp.h"
unsigned char light1,key_timernum,i;
static unsigned char uart_count;
unsigned char *a="AT+MQTTUSERCFG=0,1,\"0567df814c1a4eebbd0e7eedcdb91c0d\",\"\",\"\",0,0,\"\"\r\n";
unsigned char *b="AT+MQTTCONN=0,\"119.91.109.180\",9501,0\r\n";
unsigned char *c="AT+MQTTSUB=0,\"test\",1\r\n";

void main()
{
	Uart_Init();
	Timer0Init();
	OLED_Init();
	OLED_Clear();	
	OLED_ShowCHinese(1,0,0);
	OLED_ShowCHinese(18,0,1);
	OLED_ShowCHinese(36,0,2);
	OLED_ShowCHinese(54,0,3);
	OLED_ShowCHinese(1,3,4);
	OLED_ShowChar(18,4,':',1);
	OLED_ShowCHinese(25,3,7);	
    while(1)
  {
																	//OLED_DrawBMP(0,0,128,64,BMP2);
		key_timernum=key();
		if(key_timernum==1)
		{light1=!light1;}
		if(light1==1)
		{
		P0_1=0;
		OLED_ShowCHinese(25,3,6);
		}
		else if(light1==0)
		{
		P0_1=1;
		OLED_ShowCHinese(25,3,7);
		}
  }
}

void Uart_Routine() interrupt 4
{
	static unsigned char buzzer[20];
	if(RI==1)
	{
		RI=0;
		buzzer[i]=SBUF;
//		light1=!light1;
		if(buzzer[0]==':'||i>0)
		{i++;}
		else
		{i=0;}
	}
	if(i==13)
	{
	i=0;
	if(buzzer[12]=='1')
	{light1=1;}
	else if(buzzer[12]=='0')
	{light1=0;}
}
}

void key_num() interrupt 1
{
	static unsigned char i=0;
	static unsigned int count1,count2;
	count1++;
	count2++;
	TL0 = 0x66;
	TH0 = 0xFC;
	if(count1>=2)
	{
		key_timer();
		count1=0;
	}	
	if(count2==5000&&i==0)
	{
		i++;
		Uart_SendFile(a);
	}
	else if(count2==12000&&i==1)
	{
		i++;
		Uart_SendFile(b);
	}
	else if(count2==22000&&i==2)
	{
		i++;
		Uart_SendFile(c);
	}
}
