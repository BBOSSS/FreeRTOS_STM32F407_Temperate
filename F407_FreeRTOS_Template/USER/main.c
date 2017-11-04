/********************************************************************/
/********************************************************************/
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/********************************************************************/
/********************************************************************/
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define FLOAT_TASK_PRIO		4
//任务堆栈大小	
#define FLOAT_STK_SIZE 		128
//任务句柄
TaskHandle_t FLOATTask_Handler;
//任务函数
void float_task(void *pvParameters);
/********************************************************************/
/********************************************************************/
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		uart_init(115200); //初始化串口1-波特率：115200
		delay_init(168);   //初始化延时-系统时钟168MHz
		LED_Init();        //初始化LED-工程测试时调用
	
		//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();                              //开启任务调度
								
		for(;;);                                            //正常程序不会执行到此
}
/********************************************************************/
/********************************************************************/
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();            								 //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
  
    //浮点测试任务
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
    vTaskDelete(StartTask_Handler);                  //删除开始任务
    taskEXIT_CRITICAL();            								 //退出临界区
}

//LED0任务函数 
void led0_task(void *pvParameters)
{
   while(1)
   {
     LED_TOGGLE;
     vTaskDelay(200);
   }
}   
//浮点测试任务
void float_task(void *pvParameters)
{
	static float float_num=0.00;
	while(1)
	{
		float_num+=0.01f;
		printf("\n\r float_num: %.2f \r\n",float_num);
    vTaskDelay(200);
	}
}
/********************************************************************/
/********************************************************************/
