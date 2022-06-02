#include <reg52.h>

#define u8	 unsigned char 				//char  			8λ	  0~255
#define u16  unsigned int					//int   			16λ  0~65535
#define u32  unsigned short int		//short int   32λ
#define u64  unsigned long int		//long int   	64λ

#define  LED1 P0
#define  LED2 P1
#define  LED3 P2

#define  N  40
#define  M  100

void delay_ms(u16 ms)								//定义延时函数
{
	u8 i;
	while(ms--)
		for(i=0;i<110;i++);
}

u8 array[9]={0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0};

void main()
{
	while(1)
	{
		//逐个亮起
		u8  i = 0;
		
		u16 m = 0x0f;
		
		for(i=0;i<9;i++)
		{
			LED1 = array[i];
			delay_ms(N);
		}
		for(i=0;i<9;i++)
		{
			LED2 = array[i];
			delay_ms(N);
		}
		for(i=0;i<9;i++)
		{
			LED3 = array[i];
			delay_ms(N);
		}
		
		delay_ms(1000);
		
		//交互闪  首位亮起
		for(i=0;i<9;i++)
		{
			LED1 = array[0]<<i;
			delay_ms(M);
			LED1 = array[0]>>i;
			delay_ms(M);
			LED3 = array[0]<<i;
			delay_ms(M);
			LED3 = array[0]>>i;
			delay_ms(M);
			LED2 = array[0]<<i;
			delay_ms(M);
			LED2 = array[0]>>i;
			delay_ms(M);
		}
		//逐个熄灭
		for(i=0;i<9;i++)
		{
			LED1 = array[8-i];
			delay_ms(N);
		}
		for(i=0;i<9;i++)
		{
			LED2 = array[8-i];
			delay_ms(N);
		}
		for(i=0;i<9;i++)
		{
			LED3 = array[8-i];
			delay_ms(N);
		}
		//跑马灯 胎死腹中。
		
	}
}

/*
		
		
*/















