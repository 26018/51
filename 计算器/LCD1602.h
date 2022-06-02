#ifndef _LCD1602_H
#define _LCD1602_H
#include <intrins.h>
#include <reg52.h>

#define uint   unsigned int
#define uchar  unsigned char
#define ulong  unsigned long
	
/*------------------------------------------------
                  LCD1602位定义
------------------------------------------------*/
#define LCD1602_Data  P0
sbit    LCD1602_RS  = P3^3;
sbit    LCD1602_RW  = P3^4;
sbit    LCD1602_EN  = P3^5;

/*------------------------------------------------
                 LCD1602函数声明
------------------------------------------------*/
void LCD1602_ShowByte(uchar x,uchar y,uchar byte);
void LCD1602_ShowStr(uchar x,uchar y,uchar *str);
void LCD1602_Init(void);


#endif