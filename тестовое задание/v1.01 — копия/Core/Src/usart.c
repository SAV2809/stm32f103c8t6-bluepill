/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "adc.h"

/* USER CODE BEGIN 0 */
/* Private variables ---------------------------------------------------------*/
uint8_t UART_RX_Byte=0;
uint8_t UART_RX_Byte_huart2=0;
TStruct_Uart_State Uart_State;
uint8_t buf_huart2[2];
uint8_t val_adc[2];
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/** ****************************************************************************
  * @brief  начальная инициализация состояния uart1
  * @retval void
*******************************************************************************/
void uart_init_state_settings()
{
    Uart_State.Wait_Command=WAIT_NULL_COMMAND;
    HAL_UART_Receive_IT(&huart1, &UART_RX_Byte, 1);
    Uart_State.Queue_Status_Uart=QUEUE_STATE_EMPTY;
    //HAL_UART_Receive_IT(&huart2, &UART_RX_Byte_huart2, 2);

}
/** ****************************************************************************
  * @brief  callback ф-ия прерывания по приёму 
  * @retval void
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
    if(huart == &huart1) 
    {
        if (Uart_State.Wait_Command==WAIT_REGULAR_COMMAND) //ждём регулярную команду
        {
            uart_take_command();
            
            Uart_State.Wait_Command=WAIT_NULL_COMMAND;
        }
        else if (Uart_State.Wait_Command==WAIT_NULL_COMMAND) //проверка на первый ноль байт
        {
            if(UART_RX_Byte==0)
            {
                Uart_State.Wait_Command=WAIT_REGULAR_COMMAND;
                Uart_State.Time_Out=100;
            }
            else {uart_handler_error_first_byte();}
        }     
        HAL_UART_Receive_IT(&huart1, &UART_RX_Byte, 1);
    }
    if(huart == &huart2) 
    {
 
    }
}
/** ****************************************************************************
  * @brief  таймаут на приём регулярной команды 
  * @retval void
*******************************************************************************/
void uart_timeout()
{
    if (Uart_State.Wait_Command==WAIT_REGULAR_COMMAND)
    {
        if (Uart_State.Time_Out) Uart_State.Time_Out--;
        else Uart_State.Wait_Command=WAIT_NULL_COMMAND;
    }
}
/** ****************************************************************************
  * @brief  функция доступа к HAL_UART_Receive_IT 
  * @retval void
*******************************************************************************/
uint8_t HAL_UART_Receive_IT_user (UART_HandleTypeDef *huart)
{
    if(huart == &huart1) 
    {
        HAL_UART_Receive_IT(&huart1, &UART_RX_Byte, 1);
    }
    return 1;
    
}
/** ****************************************************************************
  * @brief  возвращает первую в очереди команду
  * @retval TStruct_Uart_Command Uart_State.Queue_Command
*******************************************************************************/
TStruct_Uart_Command uart_get_Command()
{
    /*
    if (Uart_State.Command_Active_Cnt==0)
    {
      
        while(1)
        {
          //Error
        }
      
    } 
    */
    Uart_State.Command_Active_Cnt--;
    if (Uart_State.Command_Active_Cnt==0) Uart_State.Queue_Status_Uart=QUEUE_STATE_EMPTY; 
    if (Uart_State.Await_To_Reading_Position==QUE_COMMAND_MAX){
        Uart_State.Await_To_Reading_Position=0;}
    /*
    if (Uart_State.Queue_Command[Uart_State.Await_To_Reading_Position].Place==FREE_PLACE)
    {
        
        while(1) //ловим ошибку
        {
          //Error где-то сбой, место должно было быть занято
        }
        
    }
    */
    Uart_State.Command_Complete++;
    Uart_State.Queue_Command[Uart_State.Await_To_Reading_Position].Place=FREE_PLACE;  
    return Uart_State.Queue_Command[Uart_State.Await_To_Reading_Position++];
    
}
/** ****************************************************************************
  * @brief  Процедура возвращает состояние очереди 
  * @retval Uart_State.Queue_Status_Uart
*******************************************************************************/
TEnum_Queue_State_Uart uart_get_state_queue()
{
    return Uart_State.Queue_Status_Uart;
}

/**
* @brief Обработчик ошибки.На будущее
* @retval None
*/
void uart_handler_error_first_byte()
{
    //Ошибка, пре-командный байт не равен 0
}

/**
* @brief Подпроцедура получения и сохранения команды по UART1. В конце проверяется состояние очереди (вызывается в прерывании)
* @param argument: Not used
* @retval None
*/
void uart_take_command()
{
            if (Uart_State.Command_Active_Cnt==QUE_COMMAND_MAX)
            {   
                handler_queue_not_free_place();
                
                return;
            }
            if (UART_RX_Byte==0) Uart_State.Queue_Command[Uart_State.Active_Position].Error_Satus_Command=ERROR_NULL_COMMAND;
            //сохраняем команду
            
            Uart_State.Queue_Command[Uart_State.Active_Position].Command=UART_RX_Byte;
            Uart_State.Queue_Command[Uart_State.Active_Position].NomberCommand=Uart_State.Command_Cnt;
            Uart_State.Queue_Command[Uart_State.Active_Position].Place=BUSY_PLACE;
            Uart_State.Active_Position++;
            if (Uart_State.Active_Position==QUE_COMMAND_MAX)
            {   
                Uart_State.Active_Position=0;
            }
            Uart_State.Command_Cnt++;
            Uart_State.Command_Active_Cnt++;
            //HAL_UART_Transmit_IT(&huart1, "OK", 2); //ответ
            switch (Uart_State.Command_Active_Cnt)
            {
              case                     1 ... QUE_COMMAND_MAX/2: Uart_State.Queue_Status_Uart=QUEUE_STATE_NORMAL;         break;
              case (QUE_COMMAND_MAX/2)+1 ... QUE_COMMAND_MAX-1: Uart_State.Queue_Status_Uart=QUEUE_STATE_HALF_WRITTEN;   break;
              case                           QUE_COMMAND_MAX  : Uart_State.Queue_Status_Uart=QUEUE_STATE_NOT_FREE_PLACE; break;
                
            }
}
/**
* @brief Обработчик ошибки.На будущее
* @retval None
*/
void handler_queue_not_free_place()
{
}
/**
* @brief Подпроцедура рандомно генерирует 1 из 4 возможных команд и посылает по UART2 (примет UART1). В конце проверяется состояние очереди
* @param argument: Not used
* @retval None
*/
void uart2_send_random(uint32_t task_500ms_Cnt)
{
    uint8_t t_command[2]={0,0};
    


    t_command[1]=((uint8_t)rand()%4)+1;
    HAL_UART_Transmit_IT(&huart2, t_command, 2);
    HAL_Delay(100);
    t_command[1]++;
    HAL_UART_Transmit_IT(&huart2, t_command, 2);
    
    
    /*
    if (task_500ms_Cnt==10)
    {
      t_command[1]=(1<<3)|4;
      HAL_UART_Transmit_IT(&huart2, t_command, 2);
    }
    if (task_500ms_Cnt==20)
    {
      t_command[1]=(2<<3)|4;
      HAL_UART_Transmit_IT(&huart2, t_command, 2);
      HAL_Delay(100);
    }
    */
}
/**
* @brief Подпроцедура отправляет по uart1 среднее значение ADC двумя байтами
* @param argument: Not used
* @retval None
*/
void uart_send_val_adc()
{
    val_adc[0]=(uint8_t)adc_get_adc_mean_val()<<4;
    val_adc[1]=(uint8_t)adc_get_adc_mean_val();
    HAL_UART_Transmit_IT(&huart1, val_adc, 2);
    //sprintf(
}
/**
* @brief Подпроцедура разрешает получить заданное количество байт
* @param argument: uint8_t num (количество байт)
* @retval None
*/
void uart_allow_to_receive(uint8_t num)
{
    HAL_UART_Receive_IT(&huart2, buf_huart2, num);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
