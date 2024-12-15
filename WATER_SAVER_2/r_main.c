/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.05.03.01 [12 Nov 2018]
* Device(s)    : R5F100LE
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 30-12-2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define RD_LIM 255
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include <string.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint8_t write_buffer[WR_LIM];// = "Ganesha";
uint8_t read_buffer[RD_LIM];
uint16_t ii;
extern volatile uint8_t TxFlag;
extern volatile uint8_t RxFlag;
uint8_t iCountFlag;
extern volatile uint8_t * gp_uart1_rx_address;         /* uart1 receive buffer address */
extern volatile uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern void DelayMs(uint16_t Dly);
void WifiConfig(void);
void ClrReadBuffer(void);
void ClrWriteBuffer(void);
void SendCmd(char *Buf);
void WifiReadyCheck(void);
void WifiEchoOff(void);
void WifiSsid(void);
void WifiKey(void);
void WifiWjoin(void);
void WifiNip(void);
void WifiSkct(void);
void WifiSkSnd(char *Buf);
void SendStr(char *Buf);
void LedBlink(unsigned char Repeat);
extern volatile uint8_t LeakArrestFlag;
extern volatile uint8_t DropLedFlag,DropSendFlag;
extern volatile uint32_t DropLedCounter;
extern volatile uint8_t AlmFlag;
char CmdAtPlus[] = "AT+\r";
char CmdAtPlusE[] = "AT+E\r";
char CmdAtPlusWprt[] = "AT+WPRT=0\r";
char CmdAtPlusSsid[] = "AT+SSID=Team X\r";
char CmdAtPlusKey[] = "AT+KEY=1,0,\"nknknknk\"\r";
char CmdAtPlusNip[] = "AT+NIP=1,192.168.43.7,255.255.255.0,192.168.43.1,192.168.43.1\r";
char CmdAtPlusWjoin[] = "AT+WJOIN\r";
char CmdAtPlusSkct[] = "AT+SKCT=1,0,192.168.43.121,2000,1000\r";
char CmdAtPlusSkSnd1[] = "AT+SKSND=1,1\r";
char CmdAtPlusSkSnd2[] = "AT+SKSND=1,2\r";
char CmdAtPlusSkSnd[] = "AT+SKSND=1,10\r";
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */

	WifiConfig();
	
    while (1U)
    {
	if(AlmFlag==0)
	{
		if(DropSendFlag==1)
		{
		DropSendFlag=0;
		WifiSkSnd(CmdAtPlusSkSnd);
		SendStr("< Drop. >\n"); 
		DelayMs(200);
		}
	}
	else
	{
	DropSendFlag=0;
	DelayMs(500);
	WifiSkSnd(CmdAtPlusSkSnd);
	SendStr("  Tap 01  "); 
	DelayMs(200);
	WifiSkSnd(CmdAtPlusSkSnd);
	SendStr("Leaking !\n"); 
	DelayMs(1500);
	DropSendFlag=0;
	}
	if(LeakArrestFlag==1)
	{	
	DelayMs(500);
	WifiSkSnd(CmdAtPlusSkSnd);
	SendStr("  Tap 01  "); 
	DelayMs(200);
	WifiSkSnd(CmdAtPlusSkSnd);
	SendStr(" Closed !\n"); 
	DelayMs(1500);	
	LeakArrestFlag=0;
	DropSendFlag=1;
	}
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    R_PORT_Create();
    R_INTC_Create();R_INTC4_Start();
    R_TAU0_Create();
    R_TAU0_Channel0_Start();
    R_SAU0_Create();
    R_UART1_Create();
    R_UART1_Start();
        //SEtting Up Receiving. Wait for ready message
    ii = R_UART1_Receive(read_buffer,(uint16_t)(RD_LIM));
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void LedBlink(unsigned char Repeat)
{
    for(ii=0;ii<Repeat;ii++)
    {
    LED_R=0;DelayMs(200);LED_R=1;DelayMs(200);
    }
}
void WifiConfig(void)
{
	//Hardware Reset
	
    	LED_R=1;
    	WifiReadyCheck();
	LedBlink(1);
	DelayMs(500);
    	WifiEchoOff();
	LedBlink(2);
	DelayMs(500);
    	WifiSsid();
	LedBlink(3);
	DelayMs(500);
    	WifiKey();
    	DelayMs(500);
	LedBlink(4);
    	WifiWjoin();
    	DelayMs(500);
	LedBlink(5);
    	WifiNip();
    	DelayMs(500);
	LedBlink(6);
    	WifiSkct();
    	DelayMs(500);
	LedBlink(7);
    	WifiSkSnd(CmdAtPlusSkSnd);
    	DelayMs(500);
	LedBlink(8);
    	SendStr("<<TeamX>>\n");
    	DelayMs(500);
	LED_G=0;
}
void ClrReadBuffer(void)
{
    //Clear Memory and set read_buffer address
    memset(read_buffer,0x00, 64);
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];	
}
void ClrWriteBuffer(void)
{
    //Clear Memory and set read_buffer address
    memset(write_buffer,0x00, 64);
    //g_uart1_tx_count=0;
    //gp_uart1_rx_address = &read_buffer[0];	
}
void WifiReadyCheck(void)
{
    ClrReadBuffer();
    //SendCmd(CmdAtPlus);
    WIFI_RST = 1;DelayMs(1000);WIFI_RST = 0;DelayMs(1000); WIFI_RST = 1;DelayMs(1000);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"\r\nready\r\n\r\nready\r\n");
    }while (iCountFlag!=0);	
}
void WifiEchoOff(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusE);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"AT+E\r\n+OK\r\n\r\n");
    }while (iCountFlag!=0);	
}
void WifiSsid(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusSsid);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);	
}
void WifiKey(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusKey);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);	
}
void WifiWjoin(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusWjoin);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strncmp(read_buffer,"+OK=",strlen("+OK="));
    }while (iCountFlag!=0);	
}
void WifiNip(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusNip);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);	
}
void WifiSkct(void)
{
    ClrReadBuffer();
    SendCmd(CmdAtPlusSkct);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK=1\r\n\r\n");
    }while (iCountFlag!=0);	
}

void WifiSkSnd(char *Buf)
{
    ClrReadBuffer();
    SendCmd(Buf);
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK=10\r\n\r\n");
    }while (iCountFlag!=0);	
}


void SendCmd(char *Buf)
{
    ClrWriteBuffer();
    memcpy(write_buffer,Buf,strlen(Buf));
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer));	
}

void SendStr(char *Buf)
{
    ClrWriteBuffer();
    memcpy(write_buffer,Buf,strlen(Buf));
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer));	
}
/////////////////////////////////////////////////////////////////////////////  
/*
    iCountFlag=1;
    do
    {  
    iCountFlag=(unsigned char)strcmp(read_buffer,"\r\nready\r\n");
    }while (iCountFlag!=0);
    */
/////////////////////////////////////////////////////////////////////////////    
/*
    //Clear Memory and set read_buffer address
    memset(read_buffer,0x00, 15);
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];
    //Send Echo Off Command
    memcpy(write_buffer,"AT+E\r", 5);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer));
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"AT+RSTF\r\n+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 15);
    //Send AT+ Command
    memcpy(write_buffer,"AT+\r", 4);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);    
///////////////////////////////////////////////////////////////////////////// 
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 15);
    //Send AT+WPRT=!0 Command
    memcpy(write_buffer,"AT+WPRT=!0\r", 11);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0); 
/////////////////////////////////////////////////////////////////////////////
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 30);
    //Send AT+SSID=!Team X Command
    memcpy(write_buffer,"AT+SSID=!Team X\r", 16);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0); 
/////////////////////////////////////////////////////////////////////////////    
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 30);
    //Send AT+KEY=!1,0,nknknknk Command
    memcpy(write_buffer,"AT+KEY=!1,0,\"nknknknk\"\r", 23);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
    */
///////////////////////////////////////////////////////////////////////////// 
/*
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+WJOIN Command
    memcpy(write_buffer,"AT+WJOIN\r", 9);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
*/
/*
/////////////////////////////////////////////////////////////////////////////    
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+NIP=!1 Command
    memcpy(write_buffer,"AT+NIP=!1,192.168.1.15,255.255.255.0,192.168.1.1,192.168.1.1\r", 61);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////    
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+ATM=!0 Command
    memcpy(write_buffer,"AT+ATM=!0\r", 10);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////    
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+ATRM=0,0, Command
    memcpy(write_buffer,"AT+ATRM=0,0,192.168.1.24,24000\r", 31);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////   
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+PMTF Command
    memcpy(write_buffer,"AT+PMTF\r", 8);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////   
    //Clear Memory and set read_buffer address
    g_uart1_rx_count=0;
    gp_uart1_rx_address = &read_buffer[0];   
    memset(read_buffer,0x00, 70);
    //Send AT+Z Command
    memcpy(write_buffer,"AT+Z\r", 5);
    ii = R_UART1_Send((uint8_t * const)write_buffer,strlen((const char *)write_buffer)); 
    iCountFlag=1;
    do
    {
    iCountFlag=(unsigned char)strcmp(read_buffer,"+OK\r\n\r\n");
    }while (iCountFlag!=0);
/////////////////////////////////////////////////////////////////////////////     
*/
/* End user code. Do not edit comment generated here */
