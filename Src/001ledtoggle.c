/*
 * 001ledtoggle.c
 *
 *  Created on: Jan 20, 2023
 *      Author: Saurav Uprety
 */
#include <stdio.h>
#include "stm32f446xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}


GPIO_Handle_t ledPin, btn;

uint8_t btnState;

int main(void)
{

	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = 5;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	ledPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&ledPin);

	btn.pGPIOx = GPIOC;
	btn.GPIO_PinConfig.GPIO_PinNumber = 13;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&btn);

	while(1)
	{
		btnState = GPIO_ReadFromInputPin(&btn);
		printf("%d\n", btnState);
		if(btnState == 0)
		{
			GPIO_ToggleOutputPin(&ledPin);
			delay();
		}

	}


	return -1;
}

