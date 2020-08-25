#include "led.h"


void Start_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;				 //
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);					     //根据设定参数初始化GPIO

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//上拉输入引脚
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_0);		           //PC0

    GPIO_SetBits(GPIOC,GPIO_Pin_10);						 //PC10 输出高led
    GPIO_ResetBits(GPIOC,GPIO_Pin_9);            //蜂鸣器
    GPIO_ResetBits(GPIOC,GPIO_Pin_11);		       //sg1需要充电信号
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);		       //sg2充满
    GPIO_ResetBits(GPIOC,GPIO_Pin_6);



    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9;	    		 //LED1-->PE.5 端口配置, 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				   //推挽输出 ，IO口速度为50MHz
    
		GPIO_ResetBits(GPIOB,GPIO_Pin_0); 						 //CHR  IAP程序  接触器不吸合
    GPIO_ResetBits(GPIOB,GPIO_Pin_1);              //DCHR
    GPIO_ResetBits(GPIOB,GPIO_Pin_8);	             //sg3报警
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);	             //sg4切断
}







