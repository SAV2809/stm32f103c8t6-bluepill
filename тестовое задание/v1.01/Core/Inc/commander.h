/**
  ******************************************************************************
  * @file    
  * @brief   
  ******************************************************************************
  * @attention

  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _commander_H_
#define _commander_H_

/* Includes ------------------------------------------------------------------*/
#include "types.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void commander_work();
void work_uart_command_queue();
void commander_do_command();
void get_and_execute_command();
#endif /* _commander_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
