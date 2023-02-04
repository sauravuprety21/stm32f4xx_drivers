/*
 * 002ledtoggleextbtn.c
 *
 *  Created on: Jan 20, 2023
 *      Author: Saurav Uprety
 */
#include "stm32f446xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

GPIO_Handle_t ledPin, btnPin;

uint8_t btnState;


int main(void)
{
	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = 4;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ledPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&ledPin);

	btnPin.pGPIOx = GPIOA;
	btnPin.GPIO_PinConfig.GPIO_PinNumber = 1;
	btnPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	btnPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	btnPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&btnPin);

	while(1)
	{
		btnState = GPIO_ReadFromInputPin(&btnPin);
		if(btnState == GPIO_PIN_LOW)
		{
			GPIO_ToggleOutputPin(&ledPin);
			delay();
		}
	}

}
