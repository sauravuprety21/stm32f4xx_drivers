/*
 * 004spi_tx_test.c
 *
 *  Created on: Jan. 26, 2023
 *      Author: Saurav Uprety
 */
#include "stm32f446xx.h"
#include <string.h>

/*
 * SPI2 must be configured
 *
 * Corresponding GPIO Pins must be configured to correct AF modes
 *
 *			PC_2 		--> 	SPI2_MISO				AF5			(CN7)
 *			PC_3		--> 	SPI2_MOSI				AF5			(CN7)
 *			PB_9 (D14) 	-->		SPI2_NSS (SS)			AF5			(CN10)
 *			PC_7 (D9)	--> 	SPI2_SCK (SCLK)			AF5			(CN10)
 *
 */

void SPI2_GPIOInits(void);
void SPI2_Inits(void);

SPI_Handle_t SPI2handle;


int main(void)
{
	char user_data[] = "Hello World";

	SPI2_GPIOInits();
	SPI2_Inits();


	SPI_SSIConfig(&SPI2handle, ENABLE);
	SPI_PeripheralControl(&SPI2handle, ENABLE);

	SPI_SendData(&SPI2handle, (uint8_t *)user_data, strlen(user_data));

	while(1);

	return 0;
}



void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPI2_GPIOPin;

//  Generic SPI2 GPIO Pin
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_ALTFN_MOD_5;
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;

////	SPI-2 MISO
	SPI2_GPIOPin.pGPIOx = GPIOC;
//	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
//	GPIO_Init(&SPI2_GPIOPin);

// 	SPI-2 MOSI
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPI2_GPIOPin);

//	SPI-2 SCLK
	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPI2_GPIOPin);

//// 	SPI-2 NSS
//	SPI2_GPIOPin.pGPIOx = GPIOB;
//	SPI2_GPIOPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
//	GPIO_Init(&SPI2_GPIOPin);
}


void SPI2_Inits(void)
{
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVMOD_MSTR;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUSCFG_FD;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_MAX;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI2handle);

}

