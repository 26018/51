#include <reg52.h>

#define u8	 unsigned char 				//char  			8?	  0~255
#define u16  unsigned int					//int   			16?  0~65535c g
#define u32  unsigned short int		//short int   32?
#define u64  unsigned long int		//long int   	64?
	
#define WE P1     //控制位
#define DB P0     //控制段

u8 smg_duan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xbf,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0xff};

void main()
{
	WE = 0xfe;     //最后一个为0，，第一个数码管亮
	DB = 0x01;     //最后一个为1，， a 段 亮  (为1则亮)
}