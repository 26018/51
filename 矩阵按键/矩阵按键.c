#include <reg52.h>

#define u8 unsigned char
#define u16 unsigned int
	
sbit WE1 = P1^0;
sbit WE2 = P1^1;
sbit WE3 = P1^2;
sbit WE4 = P1^3;
sbit WE5 = P1^4;
sbit WE6 = P1^5;

//#define WE P1
#define key P3
#define N 1

sbit LED = P2^5;

u8 keydata =0;

void delay(u16 i);
u8 smg_duan[17]={0,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0xff,0xef,0xf7,0x7c,0x39,0x5e,0x79,0x71,0xff};   //�����Ϊ1����
           //����   1    2    3    4     5   6    7     8    9    A   B    C    D     E   F        
 u8 key_num[16]={0xee,0xde,0xbe,0x7e,
								 0xed,0xdd,0xbd,0x7d,
								 0xeb,0xdb,0xbb,0x7b,
								 0xe7,0xd7,0xb7,0x77};

u8 datasmg[7];

								 
#ifdef _KEY_
void key_scanf(void)     //���̺���
{
	u8 key_L, key_H;
	P2 = 0xf0;  // 1111 0000      //ɨ����    ���Ǽ��̽ӿ�
	key_H = P2;
	if(key_H != 0xf0)
	{
		delay(20);
		key_H = P2;   //��״̬
		if(key_H != 0xf0)
		{
			P2 = 0x0f;
			key_L = P2;
			if(key_H == 0xe0)  //��һ�еİ�������   1110 0000
			{
				switch (key_L)  //(key_H & 0xF0) | (key_L & 0x0F)
				{								// 0xE0 | 0x0E = 0xEE;
					case 0x0e:keydata = 1; break; //��һ�� 
					case 0x0d:keydata = 5; break; //�ڶ���
					case 0x0b:keydata = 9; break; //������
					case 0x07:keydata = 13;break; //������
				}
			}
			if(key_H == 0xd0)	 //�ڶ��еİ�������   1101 0000
			{
				switch (key_L)
				{
					case 0x0e:keydata = 2; break; //��һ��
					case 0x0d:keydata = 6; break; //�ڶ���
					case 0x0b:keydata = 10;break; //������
					case 0x07:keydata = 14;break; //������
				}
			}
			if(key_H == 0xb0)  //�����еİ�������
			{
				switch (key_L)
				{
					case 0x0e:keydata = 3; break; //��һ��
					case 0x0d:keydata = 7; break; //�ڶ���
					case 0x0b:keydata = 11;break; //������
					case 0x07:keydata = 15;break; //������
				}
			}
			if(key_H == 0x70)  //�����еİ�������
			{
				switch (key_L)
				{
					case 0x0e:keydata = 4; break; //��һ��
					case 0x0d:keydata = 8; break; //�ڶ���
					case 0x0b:keydata = 12;break; //������
					case 0x07:keydata = 16;break; //������
				}
			}
			while(P2 != 0x0f);
		}
	}
}
#else

void key_scanf(void)
{
	u8 i;
	u8 key_L,key_H,key;
	P2 = 0xf0;  // 1111 0000
	key_H = P2;
	if(key_H != 0xf0)
	{
		delay(20);
		key_H = P2;
		if(key_H != 0xf0)
		{
			P2 = 0x0f;
			key_L = P2;
			key = (key_H & 0xf0) | (key_L & 0x0f);
			for(i=0;i<16;i++)
			{
				if(key == key_num[i])
					keydata = i+1;
			}
			while(P2 != 0x0f);
		}
	}
}

#endif

void main()
{
	u8 i = 0;
	LED = 0;
	
	WE1 = 1, WE2 = 1, WE3 = 1, WE4 = 1, WE5 = 1, WE6 = 1;          //���е�λ�ر�
	P0 = smg_duan[0];                  //��ʼ�� ���е� ����� ������
	
	while(1)
	{
		/*
		key_scanf();             //���̶�ȡ���� keydata
		P0 = smg_duan[keydata];     //�������ʾ������
		datasmg[0] = keydata;       //������� keydata 
		WE1 = 0;                 //ѡ����һ���˿���
		*/
		//keydata = 0;
		//P0 = smg_duan[keydata];
		
		datasmg[0] = 0;
		key_scanf(); 
		
		if(datasmg[i] != smg_duan[keydata])    //��������
		{
			i++;
			datasmg[i] = smg_duan[keydata];
		}
		
		if(datasmg[1])
		{
				P0 = datasmg[1];    
				WE1 = 0;
				delay(N);
				WE1 = 1;
		}
		
		
		if(datasmg[2])
		{
				P0 = datasmg[2];
				WE2 = 0;
				delay(N);
				WE2 = 1;
		}
		
		
		if(datasmg[3])
		{
				P0 = datasmg[3];
				WE3 = 0;
				delay(N);
				WE3 = 1;
		}
		
		
		if(datasmg[4])
		{
				P0 = datasmg[4];
				WE4 = 0;
				delay(N);
				WE4 = 1;
		}
		
		
		if(datasmg[1])
		{
				P0 = datasmg[5];
				WE5 = 0;
				delay(N);
				WE5 = 1;
		}
		
		
		if(datasmg[1])
		{
				P0 = datasmg[6];
				WE6 = 0;delay(N);
				delay(N);
				WE6 = 1;
		}
	
	}	
}

void delay(u16 i)
{
	u8 k;
	while(i--)
	{
		for(k=0;k<100;k++);
	}
}