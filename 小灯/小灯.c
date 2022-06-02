#include <reg52.h>

#define u8	 unsigned char 				//char  			8?	  0~255
#define u16  unsigned int					//int   			16?  0~65535
#define u32  unsigned short int		//short int   32?
#define u64  unsigned long int		//long int   	64?
	
#define LED P1     //¿ØÖÆÐ¡µÆ

void delay_ms(u16 ms)
{
	u8 i;
	while(ms--)
		for(i=0;i<110;i++);
}

void main()
{
	u8 s=0;
	while(1)
	{
		LED = ~(0x01 << s);   //0ÎªÁÁ
		delay_ms(80);
		s = (s+1)%9;
	}
		
}