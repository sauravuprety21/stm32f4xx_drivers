/*
@Overview 			At push of external button, trigger an interrupt whose sends "Hello World" over
					SPI from stm board to a raspberry pi. Display the message over the command-line
					on raspberry pi. Toggle an LED on btn press for debug.

@Configuration 	 	
	@btn 			GPIO Pin (PA4); External button for interrupt delivery to NVIC through EXTI4

	@spi2Handle		SPI handle struct. with pointer to SPI2 register defn pointer,
					and the SPI config. as per @Overview. Following GPIO pins used:
						MISO through GPIO PC2 with alternate function (AF5)
						MOSI through GPIO PC3 with alternate function (AF5)
						SCLK through GPIO PC7 with alternate function (AF5)
						NSS	 through GPIO PB9 with alternate function (AF5)

	@ledPin			Pin (PA1); External LED which toggles at each btn press.

	@GPIO_Init		Takes care of interrupt config. on GPIO peripheral side.
						1. Set Falling/Rising/Both trigger detection for pin on EXTI->RTSR/FTSR/RTSR & FTSR
						2. Configures GPIO port selection on SYSCFG->EXTICRx
						3. Sets (not masked) EXTI->IMR::Bitx

	@IRQConfigs			Sets up interupt config. on Arm M4 processor side
						1. Sets the NVIC_ISER (NVIC Interrupt Selection Register) based on IRQ number
						2. Sets NVIC_PR (NVIC Priority Register) 
*/
#include <stdint.h>
#include "stm32f446xx.h"
#include <string.h>


void GPIOBtnInits(void);
void GPIOLedInits(void);
void SPI2_GPIOInits(void);
void SPI2_Inits(void);
void delay(void);


GPIO_Handle_t btn, ledPin;
SPI_Handle_t spi2Handle;

char user_data[] = "Hello World";			// Payload to send over SPI

int main(void)
{
	GPIOLedInits();								// @GPIOLedInits
	GPIOBtnInits();								// @GPIOBtnInits with interrupt config. as per @GPIO_Init

	SPI2_GPIOInits();							// @SPI2_GPIOInits - Init GPIO pins dedicated to SPI
	SPI2_Inits();								// @SPI2_Inits	

	SPI_SSOEConfig(&spi2Handle, ENABLE);		// enable NSS Output in HW slave slction mode (single master)


	while(1);
	return -1;
}



/*********************************************************************************
 * @fn									- EXTI1_IRQHandler
 *
 * @brief								- Interrupt Handler for falling trigger event
 * 										  for button connected to GPIO PA4
 * @param[in]							- None
 * @return								- None
 *
 * @Note								- Toggles external LED connected to PA1 and sends
 * 										  "Hello World" over SPI2
 */
void EXTI4_IRQHandler(void)
{
	delay();															// software delay for btn debounce
	// Set (clears) EXTI->PRx (Pending Register); lets process know interrupt handled
	GPIO_IRQHandling(btn.GPIO_PinConfig.GPIO_PinNumber);		
	GPIO_ToggleOutputPin(&ledPin);										// toggle external LED

	SPI_PeripheralControl(&spi2Handle, ENABLE); 						// enable SPI2 periph.
	uint8_t dataLen = strlen(user_data);
	SPI_SendData(&spi2Handle, &dataLen, 1);								// send length information
	SPI_SendData(&spi2Handle, (uint8_t*)user_data, strlen(user_data));  // send "Hello World" over SPI2

	while(SPI_GetFlagStatus(&spi2Handle, SPI_BSY_FLAG));				// Hang while spi is busy

	SPI_PeripheralControl(&spi2Handle, DISABLE);						// disable SPI2 periph.
}



/*********************************************************************************
 * @fn									- GPIOBtnInits
 *
 * @brief								- Initialize external btn as per @btn
 * 
 * @param[in]							- None
 * @return								- None
 *
 * @Note								- 
 */
void GPIOBtnInits(void)
{
	btn.pGPIOx = GPIOA;										// pointer of GPIO_RegDef_t at base addr of GPIOA periph.

	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;		
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;		// falling trigger interrupt detection
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;	
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; 	// pin in pull, btn press forces to ground.

	GPIO_Init(&btn);										// configures GPIO pin and interrupt as per @GPIO_Init

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI4, ENABLE);			// Configure processer as per @IRQConfigs
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI4, NVIC_IRQ_PRI17);	// ^^
}



/*********************************************************************************
 * @fn									- SPI2_Inits
 *
 * @brief								- Initialize the SPI2 peripheral as per @Overview
 * 
 * @param[in]							- 
 * @return								- 
 *
 * @Note								-
 */
void SPI2_Inits(void)
{
	spi2Handle.pSPIx = SPI2;								// pointer of SPI_RegDef_t at base addr of SPI2 periph.
	spi2Handle.SPIConfig.SPI_BusConfig = SPI_BUSCFG_FD;		// SPI bus in FULL-DUPLEX mode
	spi2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVMOD_MSTR;	// stm is master; rpi is slave
	spi2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;			// data frame format - 8 bits
	spi2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI;				// DISABLE software slave mgmt (hw slave mgmg ENABLED)
	spi2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_DIV8;		// serial clock at 2 Mhz (16 Mhz DIV8)
	spi2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;			// clock phase (idle state) LOW 
	spi2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;			// clock polarity LOW - sample falling clk, shift rising clk

	SPI_Init(&spi2Handle);									// configure SPI2 bus as per config above ^
}



/*********************************************************************************
 * @fn									- SPI2_Inits
 *
 * @brief								- Initialize the GPIO pins for MOSI, MISO, NSS, SLCK as per @spi2Handle
 * 
 * @param[in]							- 
 * @return								- 
 *
 * @Note								- 
 */
void SPI2_GPIOInits(void)
{
	GPIO_Handle_t spiGPIO;

	spiGPIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;			// SPI is alternate functionality of some GPIOs
	spiGPIO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;			// Output in push-pull 
	spiGPIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	spiGPIO.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_ALTFN_MOD_5;	// SPI2 in alt function mode as per datasheet.

	spiGPIO.pGPIOx = GPIOC;											// Pointer of GPIO_RegDef_t
																	// MOSI, MSIO, and SCLK in GPIO C
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;			// Init MISO
	GPIO_Init(&spiGPIO);

	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;			// Init MOSI
	GPIO_Init(&spiGPIO);

	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;			// Init SCLK
	GPIO_Init(&spiGPIO);

	spiGPIO.pGPIOx = GPIOB;											// NSS in GPIOB port
	spiGPIO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;			// Init NSS
	GPIO_Init(&spiGPIO);
}



/*********************************************************************************
 * @fn									- delay
 *
 * @brief								- Software implemented delay to allow for button to debounce.
 * 
 * @param[in]							- None
 * @return								- None
 *
 * @Note								-
 */
void delay(void)
{
	for(uint32_t i = 0; i<500000 ; i++);
}



/*********************************************************************************
 * @fn									- GPIOLedInits
 *
 * @brief								- Init GPIO Pin (PA1) connected to external LED
 * 
 * @param[in]							- None
 * @return								- None
 *
 * @Note								-
 */
void GPIOLedInits(void)
{
	ledPin.pGPIOx = GPIOA;
	ledPin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	ledPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ledPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYP_PP;
	ledPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&ledPin);
}



