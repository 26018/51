#include <reg52.h>

#define u8	 unsigned char 				//char  			8?	  0~255
#define u16  unsigned int					//int   			16?  0~65535c g
#define u32  unsigned short int		//short int   32?
#define u64  unsigned long int		//long int   	64?
	
sbit WE1 = P1^0;
sbit WE2 = P1^1;
sbit WE3 = P1^2;
sbit WE4 = P1^3;
sbit WE5 = P1^4;
sbit WE6 = P1^5;

#define N 100

u8 datasmg[16]={0,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //数码管为1则亮
					 //数字   1    2    3    4     5   6    7     8    9    A   B    C    D     E   F   

void delay(u16 i)
{
	u8 k;
	while(i--)
	{
		for(k=0;k<100;k++);
	}
}
void main()
{
	char i=0,w=0;
	WE1 = 1, WE2 = 1, WE3 = 1, WE4 = 1, WE5 = 1, WE6 = 1;          //所有的位关闭
	
		for(i=0;i<20;i++)
	{
		if(datasmg[w+1])
		{
				P0 = datasmg[w+1];    
				WE1 = 0;
				delay(N);
				WE1 = 1;
		}
		
		if(datasmg[w+2])
		{
				P0 = datasmg[w+2];
				WE2 = 0;
				delay(N);
				WE2 = 1;
		}
		
		if(datasmg[w+3])
		{
				P0 = datasmg[w+3];
				WE3 = 0;
				delay(N);
				WE3 = 1;
		}
		
		if(datasmg[w+4])
		{
				P0 = datasmg[w+4];
				WE4 = 0;
				delay(N);
				WE4 = 1;
		}
		
		if(datasmg[w+5])
		{
				P0 = datasmg[w+5];
				WE5 = 0;
				delay(N);
				WE5 = 1;
		}
		
		if(datasmg[w+6])
		{
				P0 = datasmg[w+6];
				WE6 = 0;delay(N);
				delay(N);
				WE6 = 1;
		}
		w++;
		if(i>20)
			i=0;
		if(w>10)
			w=0;
		delay(100);
	}
}	
	
	
	
	
	
	
	
	
	
	