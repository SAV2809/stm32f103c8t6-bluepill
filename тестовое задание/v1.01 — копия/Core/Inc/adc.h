/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
typedef enum _TEnum_ADC_Freq //Error_Satus_Value
{
    ADC_FREQ_10_HZ                          =  100,
    ADC_FREQ_20_HZ                          =  50,
    ADC_FREQ_25_HZ                          =  40,
    ADC_FREQ_40_HZ                          =  25,
    ADC_FREQ_50_HZ                          =  20,
    ADC_FREQ_100_HZ                         =  10,
    ADC_FREQ_125_HZ                         =  8,
    ADC_FREQ_200_HZ                         =  5,
    ADC_FREQ_250_HZ                         =  4,
    ADC_FREQ_500_HZ                         =  2,
    ADC_FREQ_1000_HZ                        =  1,
}TEnum_ADC_Freq;                  
/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
void adc_start1();
void adc_mean_calc();
void adc_new_freq_samp(uint8_t Param_Freq);
uint16_t adc_get_adc_mean_val();
//uint16_t adc_get_adc_mean_val();

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
