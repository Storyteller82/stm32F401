/*
 * my_code.c
 *
 *  Created on: Aug 14, 2025
 *      Author: User
 */
#include "stdint.h"
#include "main.h"

volatile int16_t Counter = 0;
uint16_t Cifra = 0, Mesto = 0;
volatile uint8_t Flag_Go_Rx = 0;
extern volatile uint8_t xRx;
extern volatile uint8_t xTx;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

					//	  gfedcba
uint8_t Digit[10] = { 	0b0111111,	//0
						0b0000110,	//1
						0b1011011,	//2
						0b1001111,	//3
						0b1100110,	//4
						0b1101101,	//5
						0b1111101,	//6
						0b0000111,	//7
						0b1111111,	//8
						0b1101111 	//9
					};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == BUTTON1_Pin)
	{
		Counter++;
	}

	if (GPIO_Pin == BUTTON2_Pin)
	{
		Counter--;
	}

	if (GPIO_Pin == BUTTON3_Pin)
	{
		Flag_Go_Rx = 1;
	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//if(hspi == &hspi1)

		Counter = (int16_t) xRx;

}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//if(hspi == &hspi2)

		(int16_t) xTx++;

}

void LED_OFF ()
{
	for (uint8_t i = 0; i < 7; i++)
	{
		HAL_GPIO_WritePin(GPIOA, (1 << i), GPIO_PIN_RESET);
	}
	for (uint8_t i = 0; i < 3; i++)
	{
		HAL_GPIO_WritePin(GPIOB, (1 << i), GPIO_PIN_RESET);
	}
}

void LED_ON (uint16_t Cifra, uint16_t Mesto)
{
	LED_OFF ();

	GPIOA->ODR = Digit[Cifra];

	HAL_GPIO_WritePin(GPIOB, (1 << Mesto), GPIO_PIN_SET);
}


void Update_LED ()
{
	if (Counter == 1000)
	{
		Counter = 999;
	}

	if (Counter == -1)
	{
		Counter = 0;
	}

	if (Mesto >= 3)
	{
	    Mesto = 0;
	}

	switch (Mesto)
	{
		case 2:
		Cifra = Counter % 10;
		break;

		case 1:
		Cifra = (Counter / 10) % 10;
		break;

		case 0:
		Cifra = Counter / 100;
		break;
	}

	  LED_ON (Cifra, Mesto);

	  Mesto++;
}




