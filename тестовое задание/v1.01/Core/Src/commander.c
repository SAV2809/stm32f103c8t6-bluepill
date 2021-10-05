/**
  ******************************************************************************
  * @file commander.c   
  * @brief ������ ��������� ������ � �� ����������
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
* @brief ������ � ��������. ����������� ��������� �������, ���� �� �����, �� �������������� ����� ��������� ������
* @param None
* @retval None
*/
void work_uart_command_queue()
{
    TEnum_Queue_State_Uart Uart_Queue_State=uart_get_state_queue();
    switch (Uart_Queue_State)
    {
        case QUEUE_STATE_EMPTY:
            //todo ������ �� ������
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
* @brief ������ ���������� ������� �� �������, ��������� � ���������
* @param None
* @retval None
* @attention ����������� ������� Command_now (�������� �� �������)
             ���� ���������� ����� �� ���������, ���������� ����������
             ������� UART_COMMAND_SET_ADC_SAMPLE_RATE �������� � ����
             ������������� ������� Command_now (������� 3 ����)
             � �������� Param_Freq(������� 5 ���) ��� ���������������� ������� 
             ������������� ADC
*/
void get_and_execute_command()
{
    TStruct_Uart_Command UART_Command;
    UART_Command=uart_get_Command();
    if(commander_operation_cnt!=UART_Command.NomberCommand)
    {
        while(1) {}//����������. ���-�� ����� �� ���
    }
    uint8_t Command_now=UART_Command.Command&0x07; //������ 3 ������� ����
    uint8_t Param_Freq=UART_Command.Command&0xf8; //5 ������� ���
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
            uart_allow_to_receive(2); //��������� huart2 �������� 2 �����
            uart_send_val_adc();  //��������� adc_val (2 �����) ��� huart2 
        break;
        case UART_COMMAND_SET_ADC_SAMPLE_RATE:
            adc_new_freq_samp(Param_Freq);
        break;
    }
    commander_operation_cnt++;
}  
/***************************************************************END OF FILE****/
