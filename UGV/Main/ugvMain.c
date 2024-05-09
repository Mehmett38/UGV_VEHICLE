/*
 * ugvMain.c
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

//<<<<<<<<<<<<<<<<<<<<<-LIBRARIES->>>>>>>>>>>>>>
#include "ugvMain.h"

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
Qmc hqmc;
GPS gps;
extern SX1278_hw_t SX1278_hw;
extern SX1278_t SX1278;

//<<<<<<<<<<<<<<<<<<-STATIC FUNCTIONS->>>>>>>>>>>>>>>>>>>>>>>
static void qmcInit(I2C_HandleTypeDef *hi2c);
static void sx1278Init(SX1278_hw_t * sx1278Hw, SX1278_t * sx1278);

//<<<<<<<<<<<<<<<<<<-FUNCTIONS->>>>>>>>>>>>>>>>>>>>>>>
void ugvMain(void)
{
	BaseType_t taskStatus = pdFAIL;

	ugvSystemInit();			//!< initialize the peripherals and queue

	/*task for the motor drive*/
	taskStatus = xTaskCreate(taskSensor, "TaskMotDrive",
							 configMINIMAL_STACK_SIZE, NULL,
							 TASK_SENSOR_PRIORITY, &hTaskSensor_s);
	configASSERT(taskStatus);

	taskStatus = xTaskCreate(taskMotorDrive, "TaskMotDrive",
							 configMINIMAL_STACK_SIZE, NULL,
							 TASK_MOT_DRIVE_PRIORITY, &hTaskMotDrive_s);
	configASSERT(taskStatus);

	/*task for the lora communication*/
	taskStatus = xTaskCreate(taskLoraCom, "TaskLoraCom",
							 configMINIMAL_STACK_SIZE, NULL,
							 TASK_LORA_COM_PRIORITY, &hTaskLoraCom_s);
	configASSERT(taskStatus);

	vTaskStartScheduler();
}

/**
 * @brief initialize the peripherals
 * @return none
 */
void ugvSystemInit()
{
	  /* USER CODE BEGIN 2 */
	HAL_IWDG_Init(&hiwdg);
	UGV_cameraServoInit(&htim12, TIM_CHANNEL_1);	//!< camera servo timer init
	UGV_rcReceiverInit();							//!< enable rc receiver timer interrupt
	UGV_motorInit();								//!< enable motor driver PWM timers
	qmcInit(&hi2c1);								//!< enable i2c to read magnetometer
	init_PEC15_Table();
	sx1278Init(&SX1278_hw, &SX1278);
	databaseQueueInit(10, sizeof(LoraTransmit));	//!< sensor database queue
	GPS_Init(&huart3, &gps);
}

/**
 * @brief initial parameter of qmc5883
 * @param[in] i2c global variable
 * @return none
 */
static void qmcInit(I2C_HandleTypeDef *hi2c)
{
	HAL_GPIO_WritePin(COMPASS_VCC_GPIO_Port, COMPASS_VCC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(COMPASS_VCC_GPIO_Port, COMPASS_VCC_Pin, GPIO_PIN_SET);

	UGV_softReset();

	hqmc.qmcConfig.MODE = MODE_CONTINIOUS;
	hqmc.qmcConfig.ODR = ODR_200HZ;
	hqmc.qmcConfig.OSR = OSR_512;
	hqmc.qmcConfig.RNG = RNG_8G;
	hqmc.qmcConfig.INT = INT_DISABLE;
	hqmc.qmcConfig.ROL_PNT = ROL_PNT_ENABLE;

	reTryInit:
	if(UGV_qmcInit(hi2c, &hqmc) != HAL_OK)
	{
		goto reTryInit;
	}
	//magnetic declination of my city
	//you can learn https://www.magnetic-declination.com/
	UGV_setMagneticDelination(20, 0);
}

/**
 * @brief initialize the lore module
 * @param[in] lora pin setting
 * @param[in] lora global structure
 * @return none
 */
static void sx1278Init(SX1278_hw_t * sx1278Hw, SX1278_t * sx1278)
{
	sx1278Hw->dio0.port = DIO0_GPIO_Port;
	sx1278Hw->dio0.pin = DIO0_Pin;
	sx1278Hw->nss.port = NSS_GPIO_Port;
	sx1278Hw->nss.pin = NSS_Pin;
	sx1278Hw->reset.port = NULL;
	sx1278Hw->reset.pin = 0;
	sx1278Hw->spi = &hspi2;

	sx1278->hw = sx1278Hw;
}














