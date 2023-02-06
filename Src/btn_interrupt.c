/*
@Overview				At push of an external button, send interrupt to NVIC and implement interrupt handler
						which toggles an external LED.

@Configuration			The following pins are used:
	@btn				Pin (PA1); External button connected for interrupt delivery to NVIC through EXTI1
	
	@ledPin				Pin (PA4); External LED, output toggle by button push.

@Notes					**Details can be found in "drivers/Inc" and "drivers/Src"
	@btn 				GPIO pin is to be configured in INPUT/INTERRUPT mode.
						After the GPIO handle structure is defined, it is initialized through
						@GPIO_Init. 

	@GPIO_Init			Takes care of interrupt config. on GPIO peripheral side.
						1. Set Falling/Rising/Both trigger detection for pin on EXTI->RTSR/FTSR/RTSR & FTSR
						2. Configures GPIO port selection on SYSCFG->EXTICRx
						3. Sets (not masked) EXTI->IMR::Bitx

	@IRQConfigs			Sets up interupt config. on Arm M4 processor side
						1. Sets the NVIC_ISER (NVIC Interrupt Selection Register) based on IRQ number
						2. Sets NVIC_PR (NVIC Priority Register) based on NVIC table
 */
#include <stdint.h>
#include "stm32f446xx.h"

void delay(void);

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

	// Initialize GPIO pin connected to btn with Interrupt config. as per @GPIO_Init
	GPIO_Init(&btn);

	// Interrupt config. as per @IRQConfigs
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI1, ENABLE);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI1, NVIC_IRQ_PRI15);

	while(1);

	return -1;
}


/*********************************************************************************
 * @fn									- EXTI1_IRQHandler
 *
 * @brief								- Interrupt Handler for falling trigger event
 * 										  for button connected to GPIO PA1
 * @param[in]							- None
 * @return								- None
 *
 * @Note								-
 */
void EXTI1_IRQHandler(void)
{
	delay();
	// Set (clears) the EXTI->PRx (Pending Register); Lets processor know interrupt has been handled.
	GPIO_IRQHandling(btn.GPIO_PinConfig.GPIO_PinNumber);
	GPIO_ToggleOutputPin(&ledPin);
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

