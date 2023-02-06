/*
 * 003btnInterrupt.c
 *
 *  Created on: Jan. 22, 2023
 *      Author: Saurav Uprety
 */


#include <stdint.h>
#include "stm32f446xx.h"

void delay(void)
{
	for(uint32_t i = 0; i<500000 ; i++);
}


GPIO_Handle_t ledPin, btn;

int main(void)
{
	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&ledPin);

	btn.pGPIOx = GPIOA;
	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&btn);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI1, ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI1, NVIC_IRQ_PRI15);

	for(;;);

	return -1;
}

void EXTI1_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(btn.GPIO_PinConfig.GPIO_PinNumber);
	GPIO_ToggleOutputPin(&ledPin);
}


