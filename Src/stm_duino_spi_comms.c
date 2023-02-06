/*
 * stm_duino_spi_comms.c
 *
 *  Created on: Feb. 5, 2023
 *      Author: Saurav Uprety
 */
#include <stdint.h>
#include "stm32f446xx.h"

/*
 * Upon push of external button, send HELLO WORLD to arduino board through SPI.
 *
 * BUTTON
 *
 * 			PIN				PA4 (CN8)
 *			INPUT			Pull Up
 *
 *	SPI
 *			PC_2 			SPI2_MISO				AF5			(CN7)
 *			PC_3		 	SPI2_MOSI				AF5			(CN7)
 *			PB_9 (D14) 		SPI2_NSS (SS)			AF5			(CN10)
 *			PC_7 (D9)	 	SPI2_SCK (SCLK)			AF5			(CN10)
 *
 *
 */

GPIO_Handle_t btn;
SPI_Handle_t spi2Handle;

char user_data[] = "Hello World";

void GPIOBtnInits(void);
void SPI_GPIOInits(void);

int main(void)
{
	void GPIOBtnInits();

}


void GPIOBtnInits(void)
{
	/* Peripheral Setup for Interrupt
	 * Setup GPIO Pin A4 for Falling trigger interrupt detection */
	btn.pGPIOx = GPIOA;
	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	/* GPIO Init takes care of some interrupt configurations
	 * 1. Enables either Falling/Rising/Both trigger selection for EXTI Line corresponding to GPIO Pin
	 *    on EXTI registers
	 * 2. Configures the SYSCFG to listen to appropriate GPIO Port using EXTICR register
	 * 3. Enables SYSCFG peripherals clock in RCC
	 * 4. Sets (not masked) the Interrupt Mask Register for the EXTI line corresponding to GPIO Pin */
	GPIO_Init(&btn);

	/* Processor Side Setup for Interrupts
	 * GPIO PA4 interrupts sent through EXTI 4 line
	 * This corresponds to IRQNumber 10 (priority 17) in NVIC */
	// Enable interrupt for IRQ 10 using NVIC_ISERx
	GPIO_IRQInterruptConfig(10, ENABLE);
	// Setup priority for IRQ 10 using NVIC_IPRx
	GPIO_IRQPriorityConfig(10, 0);
}




void SPI_GPIOInits(void)
{
	GPIO_Handle_t spiGPIO;
	// GPIO Pins used for SPI using ALT Function mode (AF5)
	spiGPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	spiGPIO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	spiGPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiGPIO.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_ALTFN_MOD_5;
	// MISO , MOSI, SLCK pins lie on GPIO c
	spiGPIO.pGPIOx = GPIOC;
	// MISO
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&spiGPIO);
	// MOSI
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&spiGPIO);
	// SCLK
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&spiGPIO);
	// NSS on GPIO B9
	spiGPIO.pGPIOx = GPIOB;
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&spiGPIO);

}

void EXTI4_IRQHandler(void)
{

	// Clear the EXTI Pending Register corresponding to the GPIO Pin Number
	// Lets processor know interrupt has been taken care of
	GPIO_IRQHandling(btn.GPIO_PinConfig.GPIO_PinNumber);
}



