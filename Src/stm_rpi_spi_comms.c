/*
@Overview 			At push of a GPIO button, trigger an interrupt which sends "Hello World" over
					SPI from stm board to a raspberry pi. Display the message over the command-line
					on raspberry pi.

@Configuration 	 	The followings pins are used as described.
	@Button 		Pin (PA4); External button for interrupt delivery through EXTI4

	@SPI			MISO through GPIO PC2 with alternate function (AF5)
					MOSI through GPIO PC3 with alternate function (AF5)
					SCLK through GPIO PC7 with alternate function (AF5)
					NSS	 through GPIO PB9 with alternate function (AF5)

	@LED			Pin (PA1); External LED which toggles at each interrupt
*/

#include <stdint.h>
#include "stm32f446xx.h"
#include <string.h>


GPIO_Handle_t btn, ledPin;
SPI_Handle_t spi2Handle;

char user_data[] = "Hello World";

void GPIOBtnInits(void);
void GPIOLedInits(void);
void SPI2_GPIOInits(void);
void SPI2_Inits(void);
void delay(void);



int main(void)
{

	GPIOLedInits();
	GPIOBtnInits();

	SPI2_GPIOInits();
	SPI2_Inits();

	SPI_SSOEConfig(&spi2Handle, ENABLE);
	SPI_PeripheralControl(&spi2Handle, ENABLE);

	while(1);
	return -1;
}



void EXTI4_IRQHandler(void)
{
	delay();
	/*Clear the EXTI Pending Register corresponding to the GPIO Pin Number
	 * Lets processor know interrupt has been taken care of */
	GPIO_IRQHandling(btn.GPIO_PinConfig.GPIO_PinNumber);

	GPIO_ToggleOutputPin(&ledPin);

	SPI_SendData(&spi2Handle, (uint8_t*)user_data, strlen(user_data));
}


void GPIOBtnInits(void)
{
	btn.pGPIOx = GPIOA;
	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	/* GPIO Init takes care of some interrupt configurations
	 * 1. Enables Falling/Rising/Both trigger selection on EXTI Line
	 * 2. Configures GPIO port on SYSCFG
	 * 4. Sets (not masked) Interrupt Mask Register for EXTI line*/
	GPIO_Init(&btn);
	/* Processor Side Setup for Interrupts
	 * GPIO PA4 interrupts sent through EXTI 4 line
	 * IRQNumber 10 (priority 17) in NVIC */
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI4, ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI4, NVIC_IRQ_PRI17);
}


void SPI2_Inits(void)
{
	/*
	 * Setup the SPI2 bus for comms with rpi in full duplex mode,
	 * with stm board as master...*/
	spi2Handle.pSPIx = SPI2;
	spi2Handle.SPIConfig.SPI_BusConfig = SPI_BUSCFG_FD;
	spi2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVMOD_MSTR;
	spi2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	spi2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;
	spi2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_DIV8;
	spi2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	spi2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;

	SPI_Init(&spi2Handle);
}

void SPI2_GPIOInits(void)
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

void delay(void)
{
	for(uint32_t i = 0; i<500000 ; i++);
}


void GPIOLedInits(void)
{
	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&ledPin);
}



