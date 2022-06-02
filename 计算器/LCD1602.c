#include "LCD1602.h"
#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

#define u8 unsigned char
#define u16 unsigned int

char keydata = 0;

/*------------------------------------------------
                 LCD1602读忙函数
------------------------------------------------*/
void LCD1602_Wait(void)
{
	uchar sta;
	LCD1602_Data   = 0xff;
	LCD1602_RS     = 0;
	LCD1602_RW     = 1;
	do
	{
		LCD1602_EN = 1;
		sta        = LCD1602_Data;
		LCD1602_EN = 0;
	}while(sta & 0x80);
}
/*------------------------------------------------
                LCD1602写命令函数
------------------------------------------------*/
void LCD1602_WriteCmd(uchar cmd)
{
	LCD1602_Wait();
	LCD1602_RS  = 0;
	LCD1602_RW  = 0;
	LCD1602_Data= cmd;
	LCD1602_EN  = 1;
	LCD1602_EN  = 0;
}
/*------------------------------------------------
                 LCD1602写数据函数
------------------------------------------------*/
void LCD1602_WriteDat(uchar dat)
{
	LCD1602_Wait();
	LCD1602_RS  = 1;
	LCD1602_RW  = 0;
	LCD1602_Data= dat;
	LCD1602_EN  = 1;
	LCD1602_EN  = 0;
}
/*------------------------------------------------
                 LCD1602写地址函数
------------------------------------------------*/
void LCD1602_SetCursor(uchar x,uchar y)
{
	uchar addr;
	if(y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_WriteCmd(addr | 0x80);
}
/*------------------------------------------------
                 LCD1602写字符函数
------------------------------------------------*/
void LCD1602_ShowByte(uchar x,uchar y,uchar byte) 		//LCD1602_ShowByte(2,0,'b');
{
	LCD1602_SetCursor(x,y);
	LCD1602_WriteDat(byte);
}

/*------------------------------------------------
                 LCD1602写字符串函数
------------------------------------------------*/
void LCD1602_ShowStr(uchar x,uchar y,uchar *str)
{
	LCD1602_SetCursor(x,y);
	while(*str != '\0')
	{
		LCD1602_WriteDat(*str++);
	}
}
/*------------------------------------------------
                  LCD1602初始化函数
------------------------------------------------*/
void LCD1602_Init(void)
{
	LCD1602_WriteCmd(0x38);
	LCD1602_WriteCmd(0x0c);
	LCD1602_WriteCmd(0x06);
	LCD1602_WriteCmd(0x01);
}

void delay(u16 i)
{
	u8 k;
	while(i--)
	{
		for(k=0;k<100;k++);
	}
}

void  key_scanf(void)    //键盘函数
{
	keydata =0;    //初始化
	while(keydata == 0)
	{
		u8 key_L, key_H;
		P2 = 0xf0;  // 1111 0000      //扫描行    这是键盘接口
		key_H = P2;
		
		if(key_H != 0xf0)
		{
			delay(20);
			key_H = P2 ;  //读状态
			if(key_H != 0xf0)
			{
				P2 = 0x0f;
				key_L = P2;
				if(key_H == 0xe0)  //第一列的按键按下   1110 0000
				{
					switch (key_L)  //(key_H & 0xF0) | (key_L & 0x0F)
					{								// 0xE0 | 0x0E = 0xEE;
						case 0x0e:keydata = 1; break; //第一行 
						case 0x0d:keydata = 4; break; //第二行
						case 0x0b:keydata = 7; break; //第三行
						case 0x07:keydata = 15;break; //第四行
					}
				}
				if(key_H == 0xd0)	 //第二列的按键按下   1101 0000
				{
					switch (key_L)
					{
						case 0x0e:keydata = 2; break; //第一行
						case 0x0d:keydata = 5; break; //第二行
						case 0x0b:keydata = 8;break; //第三行
						case 0x07:keydata = 10;break; //第四行
					}
				}
				if(key_H == 0xb0)  //第三列的按键按下
				{
					switch (key_L)
					{
						case 0x0e:keydata = 3; break; //第一行
						case 0x0d:keydata = 6; break; //第二行
						case 0x0b:keydata = 9;break; //第三行
						case 0x07:keydata = 16;break; //第四行
					}
				}
				if(key_H == 0x70)  //第四列的按键按下
				{
					switch (key_L)
					{
						case 0x0e:keydata = 11; break; //第一行     A
						case 0x0d:keydata = 12; break; //第二行			D
						case 0x0b:keydata = 13;break; //第三行			C
						case 0x07:keydata = 14;break; //第四行			F
					}
				}
				while(P2 != 0x0f);
			}
		}
	}
}



char sym[17] = {'\0',49,50,'3','4','5','6','7','8','9','0','+','-','*','/','=','.'};
char get[20];
char flag;

float add(float num1,float num2)
{
	return (num1+num2);
}

float dec(float num1,float num2)
{
	return (num1-num2);
}

float mul(float num1,float num2)
{
	return (num1*num2);
}

float div(float num1,float num2)
{
	return (num1/num2);
}


void main()
{
	char i=0, w=0, x=0;    //循环变量
	float num1,num2;       //用于存储两个数字
	memset(get,'\0',20);   //用于清空数组
	
	LCD1602_Init();
	
	while(1)
	{
		key_scanf();
		
		if((1<=keydata && keydata<11) || keydata == 16)     //筛选数字以及小数点
		{
			get[w] = sym[keydata];             //保存键盘输入的字符
			w++;
		}
		else if(11<=keydata && keydata<=14)   //筛选四种算法
		{
			flag = keydata;         //flag记录算法种类
			num1 = atof(get);       //算出第一个数字    atof用于将字符串转化为浮点数
			memset(get,'\0',20);    //清空获取数字的数组
			w = 0;                  //重置循环变量
		}
		else if(keydata == 15)    //按下等于符号
		{
			float result;
			num2 = atof(get);             //获取第二个数字
			switch(flag)
			{
				case 11:result = add(num1,num2);break;    //加法
				case 12:result = dec(num1,num2);break;    //减法
				case 13:result = mul(num1,num2);break;    //乘法
				case 14:result = div(num1,num2);break;    //除法
			}
			memset(get,'\0',20);
			
			sprintf(get,"%f",result);       //浮点转化为字符串
			for(x=0;get[x]!='\0';x++)       //遍历打印
				LCD1602_ShowByte(x,1,get[x]);
		}
		LCD1602_ShowByte(i,0,sym[keydata]);   //显示键盘输入的字符
		i++;
	}
}




