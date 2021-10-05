/**
  ******************************************************************************
  * @file commander.c   
  * @brief модуль обработки команд и их выполнения
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "commander.h"
#include "usart.h"
#include "adc.h"
uint32_t commander_operation_cnt=0;
/* Private function ----------------------------------------------------------*/

void commander_work()
{
    work_uart_command_queue();
}
/**
* @brief Работа с очередью. проверяется состояние очереди, если всё плохо, то обрабатывается сразу несколько команд
* @param None
* @retval None
*/
void work_uart_command_queue()
{
    TEnum_Queue_State_Uart Uart_Queue_State=uart_get_state_queue();
    switch (Uart_Queue_State)
    {
        case QUEUE_STATE_EMPTY:
            //todo ничего не делать
        break;
        case QUEUE_STATE_NORMAL:
            get_and_execute_command();
        break;
        case QUEUE_STATE_HALF_WRITTEN:
            get_and_execute_command();
            get_and_execute_command();
        break;
        case QUEUE_STATE_NOT_FREE_PLACE:
            get_and_execute_command();
            get_and_execute_command();
            get_and_execute_command();
            get_and_execute_command();
        break;  
    }
}

/**
* @brief достаёт актуальную команду из очереди, проверяет и выполняет
* @param None
* @retval None
* @attention Принимается команда Command_now (достаётся из очереди)
             Если порядковый номер не совпадает, вызывается исключение
             Команда UART_COMMAND_SET_ADC_SAMPLE_RATE включает в себя
             идентификатор команды Command_now (младшие 3 бита)
             и параметр Param_Freq(старшие 5 бит) для конфигурирования частоты 
             дискретизации ADC
*/
void get_and_execute_command()
{
    TStruct_Uart_Command UART_Command;
    UART_Command=uart_get_Command();
    if(commander_operation_cnt!=UART_Command.NomberCommand)
    {
        while(1) {}//Исключение. что-то пошло не так
    }
    uint8_t Command_now=UART_Command.Command&0x07; //только 3 младших бита
    uint8_t Param_Freq=UART_Command.Command&0xf8; //5 старших бит
    Param_Freq=Param_Freq>>3;
    switch (Command_now)
    {
        case UART_COMMAND_LED_ON:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        break;
        case UART_COMMAND_LED_OFF:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        break;
        case UART_COMMAND_GET_ADC_AVG_VOLTAGE:
            uart_allow_to_receive(2); //разрешить huart2 получить 2 байта
            uart_send_val_adc();  //отправить adc_val (2 байта) для huart2 
        break;
        case UART_COMMAND_SET_ADC_SAMPLE_RATE:
            adc_new_freq_samp(Param_Freq);
        break;
    }
    commander_operation_cnt++;
}  
/***************************************************************END OF FILE****/
