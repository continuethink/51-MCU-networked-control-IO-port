#include <REGX52.H>

unsigned char Keynum;

void Timer0Init(void)		//1000微秒@11.0592MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	TR0=1;
}

unsigned char key_list()
{
	unsigned char num=0;
	if(P1_0==0){num=1;}
	return num;
}

void key_timer()
{
	static unsigned char last,now;
	last=now;
	now=key_list();
	if(last==1&now==0){Keynum=1;}
}

unsigned char key()
{
	unsigned char i;
	i=Keynum;
	Keynum=0;
	return i;
}
