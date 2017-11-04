/********************************************************************/
/********************************************************************/
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
/********************************************************************/
/********************************************************************/
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

//�������ȼ�
#define FLOAT_TASK_PRIO		4
//�����ջ��С	
#define FLOAT_STK_SIZE 		128
//������
TaskHandle_t FLOATTask_Handler;
//������
void float_task(void *pvParameters);
/********************************************************************/
/********************************************************************/
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		uart_init(115200); //��ʼ������1-�����ʣ�115200
		delay_init(168);   //��ʼ����ʱ-ϵͳʱ��168MHz
		LED_Init();        //��ʼ��LED-���̲���ʱ����
	
		//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();                              //�����������
								
		for(;;);                                            //�������򲻻�ִ�е���
}
/********************************************************************/
/********************************************************************/
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();            								 //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
  
    //�����������
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
    vTaskDelete(StartTask_Handler);                  //ɾ����ʼ����
    taskEXIT_CRITICAL();            								 //�˳��ٽ���
}

//LED0������ 
void led0_task(void *pvParameters)
{
   while(1)
   {
     LED_TOGGLE;
     vTaskDelay(200);
   }
}   
//�����������
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