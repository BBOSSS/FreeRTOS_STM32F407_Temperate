#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include <stdio.h>


//引脚定义
/*******************************************************/
#define USARTx                             USART1

/* 不同的串口挂载的总线不一样，时钟使能函数也不一样，移植时要注意 
 * 串口1和6是      RCC_APB2PeriphClockCmd
 * 串口2/3/4/5/7是 RCC_APB1PeriphClockCmd
 */
#define USARTx_CLK                         RCC_APB2Periph_USART1
#define USARTx_CLOCKCMD                    RCC_APB2PeriphClockCmd
#define USARTx_BAUDRATE                    115200  //串口波特率

#define USARTx_RX_GPIO_PORT                GPIOA
#define USARTx_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USARTx_RX_PIN                      GPIO_Pin_10
#define USARTx_RX_AF                       GPIO_AF_USART1
#define USARTx_RX_SOURCE                   GPIO_PinSource10

#define USARTx_TX_GPIO_PORT                GPIOA
#define USARTx_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define USARTx_TX_PIN                      GPIO_Pin_9
#define USARTx_TX_AF                       GPIO_AF_USART1
#define USARTx_TX_SOURCE                   GPIO_PinSource9

/************************************************************/
void uart_init(u32 bound);
#endif


