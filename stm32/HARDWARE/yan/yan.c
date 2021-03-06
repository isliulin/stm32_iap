#include "yan.h"
#include "stdio.h"
#include "common.h"
#include "delay.h"

void RS485_Send_D1ata(int ch)
{   
    RS485_TX_EN=1;			//设置为发送模式
    delay_ms(5);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    delay_us(5);
    USART_SendData(USART2,(unsigned char)ch);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    RS485_TX_EN=0;				//设置为接收模式
}

void Iap_RS485_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PA1端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//复位串口2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//停止复位

    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;///校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
    USART_Init(USART2, &USART_InitStructure); ; //初始化串口

//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级2级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
//
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断

    USART_Cmd(USART2, ENABLE);                    //使能串口
    RS485_TX_EN=0;			//默认为接收模式
}


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch,FILE *f)
{
    while(USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
    RS485_Send_D1ata(ch);
    while(USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
    return (ch);
}
#endif





