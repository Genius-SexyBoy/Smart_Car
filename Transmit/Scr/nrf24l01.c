


#include "nrf24l01.h"
#include "delay.h"

unsigned char const TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01}; 


unsigned char bdata sta;           //����һ���Ը�����λ����ͬʱ��ֵ
sbit	RX_DR	 = sta^6;
sbit	TX_DS  = sta^5;
sbit	MAX_RT = sta^4;	



unsigned char SPI_RW(unsigned char dat)       //дһ�ֽڲ������˵�ַ��״̬
{
 	unsigned char i;
	for(i=0;i<8;i++)
	{		
		MOSI = (dat & 0x80);
		dat <<= 1;
		SCK = 1;
		dat |= MISO;
		SCK = 0;		
	}
	return dat;
}



unsigned char SPI_RW_Reg(unsigned char reg,unsigned char value)      //дһ�ֽڵ��Ĵ���
{
 	unsigned char status;
	CSN = 0;
	status = SPI_RW(reg);               //ѡ��Ĵ�����ͬʱ����״̬��
	SPI_RW(value);                     //д���ݵ��üĴ���
	CSN = 1;
	return status;                   //����״̬�ּĴ���
}



unsigned char SPI_Read(unsigned char reg)      //��reg�Ĵ�����һ�ֽ�
{
	unsigned char value;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	SPI_RW(reg);                // ѡ��Ĵ���
  	value = SPI_RW(0);        // Ȼ��ӸüĴ���������
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(value);            // ���ؼĴ�������
}


unsigned char SPI_Write_Buf(unsigned char reg,unsigned char *pBuf,unsigned char uchars)//д����ֽڲ������˵�ַ��״̬
{
	unsigned char status,i;
	CSN = 0;
	status = SPI_RW(reg);
	for(i = 0;i < uchars;i++)
	SPI_RW(*pBuf++);
	CSN = 1;
	return status;
}


void TX_Mode(unsigned char * BUF)                                           //���÷���ģʽ
{
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
  	SPI_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0a);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	SPI_RW_Reg(WRITE_REG + RF_CH, 30);         // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	CE = 1;
}



unsigned char Check_ACK(void)
{
//	while(IRQ);                           //���ͳɹ�IRQ�Żᱻ����(IRQ���������Ǹߵ�ƽ)
//	sta = SPI_RW(NOP);                    // ����״̬�Ĵ���
//	if(MAX_RT)
//		if(clear)                         // �Ƿ����TX FIFO��û������ڸ�λMAX_RT�жϱ�־���ط�
//			SPI_RW(FLUSH_TX);
//	SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���TX_DS��MAX_RT�жϱ�־
//	IRQ = 1;
//	if(TX_DS)
//		return(0x00);
//	else
//		return(0xff);
	sta=SPI_Read(READ_REG+STATUS); // ����״̬�Ĵ���
	if(TX_DS||MAX_RT) //��������ж�
	{
		SPI_RW_Reg(WRITE_REG+STATUS,0xff); // ���TX_DS��MAX_RT�жϱ�־
		CSN=0;
		SPI_RW(FLUSH_TX);//�������FIFO �����ؼ�������Ȼ��������벻���ĺ����������Ҽ�ס���� 
		CSN=1; 
		return(0);
	}
	else
		return(1);
}



/*uchar SPI_Read_Buf(uchar reg,uchar *pBuf,uchar uchars)//������ֽڲ������˵�ַ��״̬
{
	uchar status,i;
	CSN=0;
	status=SPI_RW(reg);
	for(i=0;i<uchars;i++)
	pBuf[i]=SPI_RW(0);
	CSN=1;
	return status;	
}*/

