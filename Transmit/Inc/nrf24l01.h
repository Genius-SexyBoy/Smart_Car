


#ifndef  __NRF24L01_H__
#define  __NRF24L01_H__

#include <STC15F2K60S2.H>
#include "api.h"

#define TX_ADR_WIDTH    5   // 5 bytes TX(RX) address width
#define TX_PLOAD_WIDTH  6  // 20 bytes TX payload

sbit CE   = P0^0;
sbit CSN  = P2^7;
sbit SCK  = P0^1;
sbit MOSI = P2^6;
sbit MISO = P0^2;
sbit IRQ  = P2^5;


extern unsigned char SPI_RW(unsigned char dat);                           //дһ�ֽڲ������˵�ַ��״̬
extern unsigned char SPI_RW_Reg(unsigned char reg,unsigned char value);  //дһ�ֽڵ��Ĵ���
extern unsigned char SPI_Read(unsigned char reg);                       //��һ�ֽ�
extern unsigned char SPI_Write_Buf(unsigned char reg,unsigned char *pBuf,unsigned char uchars);//д����ֽڲ������˵�ַ��״̬
extern void TX_Mode(unsigned char * BUF);                                          //���÷���ģʽ
extern unsigned char Check_ACK(void);


#endif