/*
 * my_code.h
 *
 *  Created on: Aug 14, 2025
 *      Author: User
 */

#ifndef SRC_MY_CODE_H_
#define SRC_MY_CODE_H_



#endif /* SRC_MY_CODE_H_ */

#include "stdint.h"
#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void Update_LED ();
void LED_OFF ();
void LED_ON (uint16_t Cifra, uint16_t Mesto);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
