/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
    uint32_t task_1ms_Cnt=0; 
    uint32_t task_10ms_Cnt=0; 
    uint32_t task_500ms_Cnt=0; 

/* USER CODE END Variables */
/* Definitions for Task_1ms */
osThreadId_t Task_1msHandle;
const osThreadAttr_t Task_1ms_attributes = {
  .name = "Task_1ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_10ms */
osThreadId_t Task_10msHandle;
const osThreadAttr_t Task_10ms_attributes = {
  .name = "Task_10ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_500_ms */
osThreadId_t Task_500_msHandle;
const osThreadAttr_t Task_500_ms_attributes = {
  .name = "Task_500_ms",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Command */
osThreadId_t Task_CommandHandle;
const osThreadAttr_t Task_Command_attributes = {
  .name = "Task_Command",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_Uart_TimeO */
osThreadId_t Task_Uart_TimeOHandle;
const osThreadAttr_t Task_Uart_TimeO_attributes = {
  .name = "Task_Uart_TimeO",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Task_1ms_Handler(void *argument);
void Task_10ms_Handler(void *argument);
void Task_500_ms_Handler(void *argument);
void Task_Command_Handler(void *argument);
void Task_Uart_TimeOut_Handler(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_1ms */
  Task_1msHandle = osThreadNew(Task_1ms_Handler, NULL, &Task_1ms_attributes);

  /* creation of Task_10ms */
  Task_10msHandle = osThreadNew(Task_10ms_Handler, NULL, &Task_10ms_attributes);

  /* creation of Task_500_ms */
  Task_500_msHandle = osThreadNew(Task_500_ms_Handler, NULL, &Task_500_ms_attributes);

  /* creation of Task_Command */
  Task_CommandHandle = osThreadNew(Task_Command_Handler, NULL, &Task_Command_attributes);

  /* creation of Task_Uart_TimeO */
  Task_Uart_TimeOHandle = osThreadNew(Task_Uart_TimeOut_Handler, NULL, &Task_Uart_TimeO_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_1ms_Handler */
/**
  * @brief  Function implementing the Task_1ms thread. В этой задаче происходит оцифровка сигнала АЦП (ЦАП на моей макетке нет)
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_1ms_Handler */
void Task_1ms_Handler(void *argument)
{
  /* USER CODE BEGIN Task_1ms_Handler */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1 / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
      adc_start1();

    task_1ms_Cnt++; 
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(1);
  }
  /* USER CODE END Task_1ms_Handler */
}

/* USER CODE BEGIN Header_Task_10ms_Handler */
/**
* @brief Function implementing the Task_10ms thread. Задача проверяет не закончилось ли время ожидания регулярной команды
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_10ms_Handler */
void Task_10ms_Handler(void *argument)
{
  /* USER CODE BEGIN Task_10ms_Handler */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10 / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    uart_timeout();
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(1);
  }
  /* USER CODE END Task_10ms_Handler */
}

/* USER CODE BEGIN Header_Task_500_ms_Handler */
/**
* @brief Function implementing the Task_500_ms thread. 
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_500_ms_Handler */
void Task_500_ms_Handler(void *argument)
{
  /* USER CODE BEGIN Task_500_ms_Handler */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 500 / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
    uart2_send_random(task_500ms_Cnt);
    task_500ms_Cnt++; 
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(1);
  }
  /* USER CODE END Task_500_ms_Handler */
}

/* USER CODE BEGIN Header_Task_Command_Handler */
/**
* @brief Function implementing the Task_Command thread. Работа командного модуля
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Command_Handler */
void Task_Command_Handler(void *argument)
{
  /* USER CODE BEGIN Task_Command_Handler */

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 3000 / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
    if (task_500ms_Cnt>5)
    {
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        commander_work();
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(1);
  }
  /* USER CODE END Task_Command_Handler */
}

/* USER CODE BEGIN Header_Task_Uart_TimeOut_Handler */
/**
* @brief Function implementing the Task_Uart_TimeO thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Uart_TimeOut_Handler */
void Task_Uart_TimeOut_Handler(void *argument)
{
  /* USER CODE BEGIN Task_Uart_TimeOut_Handler */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Task_Uart_TimeOut_Handler */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
