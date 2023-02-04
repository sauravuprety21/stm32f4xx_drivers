/*
 * stm32f446xx_gpio.c
 *
 *  Created on: Jan. 17, 2023
 *      Author: Saurav Uprety
 */
#include "stm32f446xx.h"

/*********************************************************************************
 * @fn									-
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 * @Note								-
 */


/*********************************************************************************
* @fn									- GPIO_PeriClockControl
 *
 * @brief								- Enable or Disable peripheral clock in RCC for given GPIO port
 * @param[in]							- Base address of GPIO port
 * @param[in]							- ENABLE (0) or DISABLE (1) macros
 *
 * @return								- void
 *
 * @Note								-
 */
void GPIO_PeriClockControl(GPIO_RegDef_t __vo *const pGPIOx, uint8_t const EnorDi)
{
	intptr_t GPIOPort = (intptr_t) pGPIOx;

	if(EnorDi)
	{
		switch (GPIOPort)
		{
			case (GPIOA_BASEADDR):
				GPIOA_PCLK_EN();
				break;
			case (GPIOB_BASEADDR):
				GPIOB_PCLK_EN();
				break;
			case (GPIOC_BASEADDR):
				GPIOC_PCLK_EN();
				break;
			case (GPIOD_BASEADDR):
				GPIOD_PCLK_EN();
				break;
			case (GPIOE_BASEADDR):
				GPIOE_PCLK_EN();
				break;
			case (GPIOF_BASEADDR):
				GPIOF_PCLK_EN();
				break;
			case (GPIOG_BASEADDR):
				GPIOG_PCLK_EN();
				break;
			case (GPIOH_BASEADDR):
				GPIOH_PCLK_EN();
				break;
		}
	} else {
		switch (GPIOPort)
		{
			case (GPIOA_BASEADDR):
				GPIOA_PCLK_DI();
				break;
			case (GPIOB_BASEADDR):
				GPIOB_PCLK_DI();
				break;
			case (GPIOC_BASEADDR):
				GPIOC_PCLK_DI();
				break;
			case (GPIOD_BASEADDR):
				GPIOD_PCLK_DI();
				break;
			case (GPIOE_BASEADDR):
				GPIOE_PCLK_DI();
				break;
			case (GPIOF_BASEADDR):
				GPIOF_PCLK_DI();
				break;
			case (GPIOG_BASEADDR):
				GPIOG_PCLK_DI();
				break;
			case (GPIOH_BASEADDR):
				GPIOH_PCLK_DI();
				break;
		}
	}
}


/*********************************************************************************
 * @fn									- GPIO_Init
 *
 * @brief								- Initialize the GPIO pin
 * @param[in]							- Pointer to handle structure of GPIO Pin
 * @param[in]							-
 *
 * @return								- void
 * @Note								-
 */
void GPIO_Init(GPIO_Handle_t __vo *const pGPIOHandle)
{
	uint32_t temp = 0;

	// Enable GPIO port clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	// Configure GPIO mode (non-interrupt)
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANLG)
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp = 0;
	} else
	{
		// Configure interrupt mode
		switch(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode)
		{
			case GPIO_MODE_IT_FT: 		// configure FTSR
				EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				break;

			case GPIO_MODE_IT_RT:		// configure RTSR
				EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				break;

			case GPIO_MODE_IT_RFT:		// configure both
				EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				break;
		}
		uint8_t temp1, temp2, portCode;
		intptr_t GPIOPort;

		temp1 = (uint8_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		temp2 = (uint8_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		GPIOPort = (intptr_t) pGPIOHandle->pGPIOx;

		switch (GPIOPort)
		{
			case GPIOA_BASEADDR:
				portCode = 0;
				break;
			case GPIOB_BASEADDR:
				portCode = 1;
				break;
			case GPIOC_BASEADDR:
				portCode = 2;
				break;
			case GPIOD_BASEADDR:
				portCode = 3;
				break;
			case GPIOE_BASEADDR:
				portCode = 4;
				break;
			case GPIOF_BASEADDR:
				portCode = 5;
				break;
			case GPIOG_BASEADDR:
				portCode = 6;
				break;
			case GPIOH_BASEADDR:
				portCode = 7;
				break;
			default:
				portCode = 0;
		}
		SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4));
		SYSCFG->EXTICR[temp1] |= (portCode << (temp2 * 4));

		// Configure GPIO port selection in SYSCFG_EXTICR
		SYSCFG_PCLK_EN();

		// Enable EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	// Configure GPIO output speed
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDER &= ~(0x3 << 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDER |= temp;
	temp = 0;

	// Configure GPIO pull up pull down
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;

	// Configure GPIO output type
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;

	// Configure GPIO alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1, temp2;

		temp1 = (int) pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = (int) pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2);
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << 4 * temp2);
		pGPIOHandle->pGPIOx->AFR[temp1] |= temp;
		temp = 0;
	}

}


/*********************************************************************************
 * @fn									- GPIO_DeInit
 *
 * @brief								- Deinit GPIO port using RCC_AHB1RSTR register
 * @param[in]							- GPIO port base address
 *
 * @return								- void
 * @Note								-
 */
void GPIO_DeInit(GPIO_RegDef_t __vo *const pGPIOx)
{
	intptr_t GPIOPort = (intptr_t)pGPIOx;
	switch (GPIOPort)
	{
		case (GPIOA_BASEADDR):
			GPIOA_REG_RESET();
			break;
		case (GPIOB_BASEADDR):
			GPIOB_REG_RESET();
			break;
		case (GPIOC_BASEADDR):
			GPIOC_REG_RESET();
			break;
		case (GPIOD_BASEADDR):
			GPIOD_REG_RESET();
			break;
		case (GPIOE_BASEADDR):
			GPIOE_REG_RESET();
			break;
		case (GPIOF_BASEADDR):
			GPIOF_REG_RESET();
			break;
		case (GPIOG_BASEADDR):
			GPIOG_REG_RESET();
			break;
		case (GPIOH_BASEADDR):
			GPIOH_REG_RESET();
			break;
	}

}



/*********************************************************************************
 * @fn									- ReadFromInputPin
 *
 * @brief								- Read from GPIO Input PIn
 * @param[in]							- Base address of GPIO port
 * @param[in]							- GPIO Pin number
 *
 * @return								- Pin current state
 * @Note								-
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Handle_t __vo *const pGPIOHandle)
{
	uint8_t value;
	value = (uint8_t)(pGPIOHandle->pGPIOx->IDR >> pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) & 0x0000001;
	return value;
}


/*********************************************************************************
 * @fn									- ReadFromInputPprt
 *
 * @brief								- Read state of all pins in GPIO port
 * @param[in]							- Base address of GPIO port
 * @param[in]							-
 *
 * @return								- Current states of all pins
 * @Note								-
 */
uint16_t GPIO_ReadFromInputPort(GPIO_Handle_t __vo *const pGPIOHandle)
{
	uint16_t value;
	value = (uint16_t) (pGPIOHandle->pGPIOx->IDR);
	return value;
}


/*********************************************************************************
 * @fn									- GPIO_WriteToOutputPin
 *
 * @brief								- Write a state to certain GPIO pin
 * @param[in]							- Base address of GPIO port
 * @param[in]							- GPIO pin number
 * @param[in]							- Value to write
 *
 * @return								- None
 * @Note								-
 */
void GPIO_WriteToOutputPin(GPIO_Handle_t __vo *const pGPIOHandle, uint8_t Value)
{
	if(Value)
		pGPIOHandle->pGPIOx->ODR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	else
		pGPIOHandle->pGPIOx->ODR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
}


/*********************************************************************************
 * @fn									- GPIO_WriteToOutputPort
 *
 * @brief								- Write a state to all pins in GPIO port
 * @param[in]							- Base address of GPIO port
 * @param[in]							- Value to write
 *
 * @return								- None
 * @Note								-
 */
void GPIO_WriteToOutputPort(GPIO_Handle_t __vo *const pGPIOHandle, uint16_t const Value)
{
	pGPIOHandle->pGPIOx->ODR = Value;
}


/*********************************************************************************
 * @fn									- GPIO_ToggleOutputPin
 *
 * @brief								- Toggle the state of a certain GPIO pin
 * @param[in]							- Base address of GPIO port
 * @param[in]							- GPIO pin number
 *
 * @return								- None
 * @Note								-
 */
void GPIO_ToggleOutputPin(GPIO_Handle_t __vo *const pGPIOHandle)
{
	pGPIOHandle->pGPIOx->ODR ^= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
}


/*********************************************************************************
 * @fn									- GPIO_IRQConfig
 *
 * @brief								- Enable or Disable interrupt request  in NVIC
 * @param[in]							- Interrupt Request number
 * @param[in]							- Enable or Disable
 *
 * @return								-
 * @Note								-
 */
void GPIO_IRQInterruptConfig(uint8_t const IRQNumber, uint8_t const EnorDi)
{
	if(EnorDi)
	{
		if ((IRQNumber < 32) && (IRQNumber > 0)){
			*NVIC_ISER0 |= (1 << IRQNumber);
		} else if (IRQNumber < 64) {
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		} else if (IRQNumber < 96) {
			*NVIC_ISER1 |= (1 << (IRQNumber % 64));
		}
	} else {
		if ((IRQNumber < 32) && (IRQNumber > 0)){
			*NVIC_ICER0 |= (1 << IRQNumber);
		} else if (IRQNumber < 64) {
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		} else if (IRQNumber < 96) {
			*NVIC_ICER1 |= (1 << (IRQNumber % 64));
		}
	}
}


/*********************************************************************************
 * @fn									- GPIO_IRQPriorityConfig
 *
 * @brief								- Configure the IRQ priority number in NVIC
 * @param[in]							- IRQ number
 * @param[in]							- IRQ priority
 *
 * @return								-
 * @Note								-
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	*(NVIC_PR_BASEADDR + (4*iprx)) &= ~(0xFF << (8 * iprx_section + 4));
	*(NVIC_PR_BASEADDR + (4*iprx)) |= (IRQPriority << (8 * iprx_section + 4));
}


/*********************************************************************************
 * @fn									- GPIO_IRQHandling
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 * @Note								-
 */
void GPIO_IRQHandling(uint8_t const PinNumber)
{
	if(EXTI->PR & (1 << PinNumber))
	{
		// Clear
		EXTI->PR |= (1 << PinNumber);
	}
}










