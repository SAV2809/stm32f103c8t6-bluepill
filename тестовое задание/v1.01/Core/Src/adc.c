/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "types.h"
uint16_t adc;
uint32_t adc_sum;
uint16_t adc_mean_val;
uint16_t adc_mean_cnt=1000;
uint16_t ADC_Tick=0;
TEnum_ADC_Freq ADC_Freq=ADC_FREQ_1000_HZ;
bool DMA_Data_Received=1;
/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_NORMAL;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
* @brief ����������� ������������������ �������, ���� ������ �����, �� ����������� �������������� ADC, �������� adc_start2()
* @param None
* @retval None
*/
void adc_start1()

{
    ADC_Tick++;
    if (ADC_Tick==(uint16_t)ADC_Freq)
    {
        ADC_Tick=0;
        void adc_start2();
    }
}
/**
* @brief ������ ��������������, ������� �������� �������� �������� adc_mean_calc()
* @param None
* @retval None
*/
void adc_start2()
{
    if(DMA_Data_Received)
    {
        DMA_Data_Received=0;
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc, 1);
    }
    adc_mean_calc();
}/**
* @brief ������� �������
* @param None
* @retval None
*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1) 
    {
        DMA_Data_Received=1;
    }
}

/**
* @brief ������� �������� �������� �� ���
* @param None
* @retval None
* @attention ������������� ����� �������� � ������� �� ���������� ������� � ���
             ����������� �������� �������� � adc_mean_val
*/
void adc_mean_calc()
{
        //������� �������� �� 1� 
    adc_mean_cnt=(uint16_t)ADC_Freq;
    if (adc_mean_cnt)
    {
        adc_mean_cnt--;
        adc_sum=adc_sum+adc;
    }
    else 
    {  
        if (adc_sum==0) {adc_mean_val=0; return;}
        adc_mean_val=(uint16_t)(adc_sum/(uint32_t)ADC_Freq);
        adc_mean_cnt=(uint16_t)ADC_Freq;
        adc_sum=0;    
    }
}
/**
* @brief �������� ���������� ������� �������� ADC
* @param None
* @retval adc_mean_val
*/
uint16_t adc_get_adc_mean_val()
{
    return adc_mean_val;
}
/**
* @brief ��������� ������������� ������� ������������� ADC
* @param uint8_t Param_Freq, �������� ���������� �� 5 ������� ��� �������
* @retval None
*/
void adc_new_freq_samp(uint8_t Param_Freq)
{
    switch (Param_Freq)
    {
        case 1 : ADC_Freq=ADC_FREQ_10_HZ;   break;
        case 2 : ADC_Freq=ADC_FREQ_20_HZ;   break;
        case 3 : ADC_Freq=ADC_FREQ_25_HZ;   break;
        case 4 : ADC_Freq=ADC_FREQ_40_HZ;   break;
        case 5 : ADC_Freq=ADC_FREQ_50_HZ;   break;
        case 6 : ADC_Freq=ADC_FREQ_100_HZ;  break;
        case 7 : ADC_Freq=ADC_FREQ_125_HZ;  break;
        case 8 : ADC_Freq=ADC_FREQ_200_HZ;  break;
        case 9 : ADC_Freq=ADC_FREQ_250_HZ;  break;
        case 10: ADC_Freq=ADC_FREQ_500_HZ;  break;
        case 11: ADC_Freq=ADC_FREQ_1000_HZ; break;    
    }
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
