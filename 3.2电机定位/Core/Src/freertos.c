/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "Key.h"
#include "OLED.h"
#include "myusart.h"
#include "ecoder.h"
#include "myADC.h"
#include "PWM.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern TIM_HandleTypeDef htim2;

int16_t location;
uint16_t ADC_1,ADC_2;
float actual,target=0,out,cur_error,error_Int;
float kp,ki,kd;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/**
  * @brief  OLED显示屏部分
  * @param  无
  * @retval 无
  */
void Test_OLED(void *argument)
{
	OLED_Init();
	
	OLED_ShowString(1,1,"Tar:");
	OLED_ShowString(1,9,"Act:");
	OLED_ShowString(2,1,"Ac:");
	OLED_ShowString(2,9,"Lo:");
  OLED_ShowString(2,1,"Out:");
  OLED_ShowString(3,1,"Kp:");
  OLED_ShowString(3,9,"Ki");
	OLED_ShowString(4,1,"kd:");
	
	while(1)
	{
		OLED_ShowSignedNum(1,5,target,3);
		OLED_ShowSignedNum(1,13,actual,3);
		OLED_ShowSignedNum(2,12,location,4);
    OLED_ShowSignedNum(2,5,out,2);
    OLED_ShowNum(3,4,kp,2);
    
    OLED_ShowFloat(3,4,kp,1,2);
    OLED_ShowFloat(3,11,ki,1,3);
    OLED_ShowFloat(4,4,kd,1,2);
		
		
		osDelay(40);
	}
}

/**
  * @brief  串口部分
  * @param  无
  * @retval 无
  */
void Test_Usart(void *argument)
{
  while (1)
  {
    Send_JustFloat(target,actual,cur_error,out);
		osDelay(40);
  }
}

/**
  * @brief  电机部分
  * @param  无
  * @retval 无
  */
void Test_Motor(void *argument)
{
	
	Key_Init();
	PWM_Init();

	while(1)
	{
//   if(target>40)
//   {
//    target=0;
//   }
   if(Key_Get(0)) 
   {
    target+=20;
   }
   if(kd>2)
   {
    kd=0;
   }
   if(Key_Get(1))
   {
    kd+=0.02;;
   }
			// PWM=(float)ADC*100/2048-100;
      // PWM_Set(PWM);
      osDelay(20);
	}
}

/**
  * @brief  编码器部分
  * @param  无
  * @retval 无
  */
void Test_Ecoder(void *argument)
{
	ecoder_Init();

	while(1)
	{
		osDelay(40);
	}
}

/**
  * @brief  模转数部分
  * @param  无
  * @retval 无
  */
void Test_ADC(void *argument)
{
	MyADC_Init();
	while(1)
	{
	  ADC_1=Get_ADC(hadc1);
    ADC_2=Get_ADC(hadc2);
    kp=ADC_1/4095.0f*8;
    ki=ADC_2/4095.0f*4;
		osDelay(40);
	}
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xTaskCreate(Test_OLED,"TestOLED",64,NULL,osPriorityNormal,NULL);
	xTaskCreate(Test_Motor,"TestMotor",64,NULL,osPriorityNormal,NULL);
	xTaskCreate(Test_ADC,"TestADC",64,NULL,osPriorityNormal,NULL);
	xTaskCreate(Test_Ecoder,"TestEcoder",64,NULL,osPriorityNormal,NULL);
  xTaskCreate(Test_Usart,"TestUsart",64,NULL,osPriorityNormal,NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
//    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

