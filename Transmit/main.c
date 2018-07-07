#include  <STC15F2K60S2.H>
#include  "api.h"
#include  "nrf24l01.h"
#include  "uart.h"
#include  "delay.h"
#include  "oled12864.h"


sbit KEY1 = P5^0;
sbit KEY2 = P5^1;
sbit KEY3 = P4^5;
sbit KEY4 = P4^0;
//sbit KEY5 = P2^6;
sbit LED  = P5^5;
unsigned char TX_BUF[TX_PLOAD_WIDTH];

void GPIO_Init(void)
{
	P1M0 = 0; 		 P1M1 = 0;
	P2M0 = 0; 		 P2M1 = 0;
	P3M0 = 0; 		 P3M1 = 0;
	P4M0 = 0; 		 P4M1 = 0;
	P5M0 = 0; 		 P5M1 = 0;
}

void OLED_Init(void)
{
	    LCD_CS= 0;
		  LCD_Init();   		
		  LCD_Fill(0xff); 
			delay_ms(100); 
		  LCD_Fill(0x00);
			delay_ms(100);     
		  LCD_CLS();
		  delay_ms(100);  
			delay_ms(1);
}	




void KeyScan(void)
{
	
	if(!KEY1)                              //�����⵽�͵�ƽ��˵����������
	{
		delay_ms(20);                       //��ʱȥ����һ��10-20ms
		if(!KEY1)                         //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			LED = 0;
			while(!KEY1);         
			//���ȷ�ϰ��°����ȴ������ͷţ�û�����˳�
			{
				LCD_Fill(0x00);
				TX_BUF[0] = 1;            //����ת
				TX_BUF[1] = 0;
				TX_BUF[2] = 0;
				TX_BUF[3] = 1;
				TX_BUF[4] = 0x11;
				TX_BUF[5] = 0x11;
				TX_Mode(TX_BUF);  //��������
				delay_ms(50);
		//		SPI_RW_Reg(WRITE_REG+STATUS,0xff); // ���TX_DS��MAX_RT�жϱ�־
					while(Check_ACK());      //����Ƿ������
		//		SPI_RW(FLUSH_TX);//�������FIFO
				SendString("��ת\n");	
				LCD_P6x8Str(15,1,"Smart Flying Car");
				LCD_P6x8Str(15,8,"Smart Flying Car");
				LCD_P6x8Str(20,4,"Current State:");
				LCD_P6x8Str(30,5,"Turn Left");	
				SendString("Waiting for commend:......\n");			
				LED = 1;
			//	SPI_RW_Reg(WRITE_REG+STATUS,0xff); //���״̬�Ĵ���
			}
		}
	}

	else if(!KEY2)                                //�����⵽�͵�ƽ��˵����������
	{
		delay_ms(20);                              //��ʱȥ����һ��10-20ms
		if(!KEY2)                                //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			LED = 0;
			while(!KEY2);                        //���ȷ�ϰ��°����ȴ������ͷţ�û�����˳�
			{
				LCD_Fill(0x00);
				TX_BUF[0] = 0;                   //����ת
				TX_BUF[1] = 1;
				TX_BUF[2] = 1;
				TX_BUF[3] = 0;
				TX_BUF[4] = 0x22;
				TX_BUF[5] = 0x22;
				TX_Mode(TX_BUF);        //��������
				delay_ms(50);
			//	SPI_RW_Reg(WRITE_REG+STATUS,0xff); // ���TX_DS��MAX_RT�жϱ�־
				while(Check_ACK());      //����Ƿ������
			//	SPI_RW(FLUSH_TX);//�������FIFO
				SendString("��ת\n");
				LCD_P6x8Str(15,1,"Smart Flying Car");
				LCD_P6x8Str(15,8,"Smart Flying Car");
				LCD_P6x8Str(20,4,"Current State:");
				LCD_P6x8Str(30,5,"Turn Right");
				SendString("Waiting for commend:......\n");
				LED = 1;
			//	SPI_RW_Reg(WRITE_REG+STATUS,0xff); //���״̬�Ĵ���
			}
		}
	}
	
	else if(!KEY3)                             //�����⵽�͵�ƽ��˵����������
	{  
		delay_ms(20);                           //��ʱȥ����һ��10-20ms
		if(!KEY3)                             //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			LED = 0;
			while(!KEY3);                     //���ȷ�ϰ��°����ȴ������ͷţ�û�����˳�
			{
				LCD_Fill(0x00);
				TX_BUF[0] = 1;                //ǰ��
				TX_BUF[1] = 0;
				TX_BUF[2] = 1;
				TX_BUF[3] = 0;
				TX_BUF[4] = 0x33;
				TX_BUF[5] = 0x33;
				TX_Mode(TX_BUF);     //��������
				delay_ms(50);
			//	SPI_RW_Reg(WRITE_REG+STATUS,0xff); // ���TX_DS��MAX_RT�жϱ�־
					while(Check_ACK());      //����Ƿ������
			//	SPI_RW(FLUSH_TX);//�������FIFO
				SendString("ǰ��\n");
				SendString("Waiting for commend:......\n");
				LCD_P6x8Str(15,1,"Smart Flying Car");
				LCD_P6x8Str(15,8,"Smart Flying Car");
				LCD_P6x8Str(20,4,"Current State:");
				LCD_P6x8Str(30,5,"Go Back");
				LED = 1;
		//		SPI_RW_Reg(WRITE_REG+STATUS,0xff); //���״̬�Ĵ���
			}
		}
	}

	else if(!KEY4)                            //�����⵽�͵�ƽ��˵����������
	{
		delay_ms(20);                           //��ʱȥ����һ��10-20ms
		if(!KEY4)                             //�ٴ�ȷ�ϰ����Ƿ��£�û�а������˳�
		{
			LED = 0;
			while(!KEY4);                      //���ȷ�ϰ��°����ȴ������ͷţ�û�����˳�
			{
				LCD_Fill(0x00);
				TX_BUF[0] = 0;						      //����
				TX_BUF[1] = 1;
				TX_BUF[2] = 0;
				TX_BUF[3] = 1;
				TX_BUF[4] = 0x44;
				TX_BUF[5] = 0x44;
				TX_Mode(TX_BUF);        //��������
				delay_ms(50);
				//SPI_RW_Reg(WRITE_REG+STATUS,0xff); // ���TX_DS��MAX_RT�жϱ�־
				while(Check_ACK());      //����Ƿ������
			//	SPI_RW(FLUSH_TX);//�������FIFO
				SendString("����\n");
				SendString("Waiting for commend:......\n");
				LCD_P6x8Str(15,1,"Smart Flying Car");
				LCD_P6x8Str(15,8,"Smart Flying Car");
				LCD_P6x8Str(20,4,"Current State:");
				LCD_P6x8Str(30,5,"Go Ahead");
				LED = 1;
			//	SPI_RW_Reg(WRITE_REG+STATUS,0xff); //���״̬�Ĵ���
			}

		}
	}
	else
	{
		//LCD_Fill(0x00);
		TX_BUF[0] = 1;						      //ɲ��
		TX_BUF[1] = 1;
		TX_BUF[2] = 1;
		TX_BUF[3] = 1;
		TX_BUF[4] = 0x55;
		TX_BUF[5] = 0x55;
		TX_Mode(TX_BUF);        //��������
		delay_ms(50);
		while(Check_ACK());      //����Ƿ������
		LCD_P6x8Str(15,1,"Smart Flying Car");
		LCD_P6x8Str(15,7,"Smart Flying Car");
//		LCD_P6x8Str(10,4,"Current State:");
//		LCD_P6x8Str(20,5,"Go Back");
	}

}


  
void main (void)
{
	GPIO_Init();
	UartInit();
	OLED_Init();
	delay_ms(200);
	SendString("Waiting for commend:......\n");
	LCD_P6x8Str(15,1,"Smart Flying Car");
	LCD_P6x8Str(15,8,"Smart Flying Car");
	while(1)
	{
		LED =1;
		SPI_RW_Reg(WRITE_REG+STATUS,0xff); 
		KeyScan();
	}
}

