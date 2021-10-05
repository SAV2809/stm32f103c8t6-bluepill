/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

  
  

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define QUE_COMMAND_MAX 10

#define UART_COMMAND_LED_ON                   1
#define UART_COMMAND_LED_OFF                  2
#define UART_COMMAND_GET_ADC_AVG_VOLTAGE      3
#define UART_COMMAND_SET_ADC_SAMPLE_RATE      4

/* Exported types ------------------------------------------------------------*/
typedef enum _TEnum_Place
{
    FREE_PLACE                =  01,     
    BUSY_PLACE                =  02,  
}TEnum_Place;

typedef enum _TEnum_Wait_Command
{
    WAIT_NULL_COMMAND                =  01,     
    WAIT_REGULAR_COMMAND             =  02,   
}TEnum_Wait_Command;

typedef enum _TEnum_Error_Status_Command //Error_Satus_Value
{
    ERROR_NULL_COMMAND                =  01,   
    ERROR_INCORRECT_COMMAND           =  02,    
}TEnum_Error_Status_Command;

typedef enum _TEnum_Queue_State_Uart //Error_Satus_Value
{
    QUEUE_STATE_EMPTY                       =  00,
    QUEUE_STATE_NORMAL                      =  01,
    QUEUE_STATE_HALF_WRITTEN                =  02,
    QUEUE_STATE_NOT_FREE_PLACE              =  03,
}TEnum_Queue_State_Uart;

typedef struct _TStruct_Uart_Command
{
    uint32_t                            NomberCommand          :32;    //порядковый номер команды от начала работы программы
    uint8_t                             Command               :8;    //сама команда
    //uint8_t                             Param                 :8     //частота
    TEnum_Place                         Place                 :2;    //свободно ли место FREE_PLACE или BUSY_PLACE 
    TEnum_Error_Status_Command          Error_Satus_Command   :2;    
}TStruct_Uart_Command;


typedef struct _TStruct_Uart_State
{
    uint8_t                     Time_Out;  // таймаут 
    uint32_t                    Command_Cnt; //сколько всего было команд за всё время
    uint32_t                    Command_Active_Cnt; //количество активных команд (ждущих обработки)
    uint32_t                    Active_Position; //указатель на текущее пустое место для новой записи
    uint32_t                    Await_To_Reading_Position; //кто первый в очереди на считывание
    TEnum_Wait_Command          Wait_Command;
    uint32_t                    Command_Complete; //счётчик отданых на обработку команд
    TStruct_Uart_Command        Queue_Command[QUE_COMMAND_MAX]; //очередь
    TEnum_Queue_State_Uart      Queue_Status_Uart;
}TStruct_Uart_State;

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) ;
uint8_t HAL_UART_Receive_IT_user (UART_HandleTypeDef* huart);
TStruct_Uart_Command uart_get_Command();
void UART_decrement_Index(void);
void uart_handler_error_first_byte();
void uart_init_state_settings();
void uart_take_command();
void handler_queue_not_free_place();
TEnum_Queue_State_Uart uart_get_state_queue();
void uart2_send_random(uint32_t);
void uart_allow_to_receive(uint8_t);
void uart_send_val_adc();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
