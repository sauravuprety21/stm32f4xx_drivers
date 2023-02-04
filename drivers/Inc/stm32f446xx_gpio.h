/*
 * stm32f446xx_gpio.h
 *
 *  Created on: Jan. 17, 2023
 *      Author: Saurav Uprety
 */

#ifndef INC_STM32F446XX_GPIO_H_
#define INC_STM32F446XX_GPIO_H_

/*
 * GPIO pin configuration structure
 */
typedef struct
{
	uint8_t GPIO_PinNumber;					/*|< Possible values from @GPIO_PIN_NUMBER>*/
	uint8_t GPIO_PinMode;					/*|< Possible values from @GPIO_PIN_MODES>*/
	uint8_t GPIO_PinSpeed;					/*|< Possible values from @GPIO_PIN_OSPEED*/
	uint8_t GPIO_PinPuPdControl;			/*|< Possible values from @GPIO_PIN_PUPD>*/
	uint8_t GPIO_PinOPType;					/*|< Possible values from @GPIO_PIN_OTYP>*/
	uint8_t GPIO_PinAltFunMode;				/*|< Possible values from @GPIO_ALTFN_MODS>*/
}GPIO_PinConfig_t;


/*
 * GPIO pin handle structure
 */
typedef struct
{
	GPIO_RegDef_t *pGPIOx;					/*|< Base address to GPIO Port to which the pin belongs>*/
	GPIO_PinConfig_t GPIO_PinConfig;		/*|< Holds GPIO pin configuration>*/
}GPIO_Handle_t;



/*
 * GPIO pin numbers
 * @GPIO_PIN_NUMBER
 */
#define GPIO_PIN_NO_0 			0
#define GPIO_PIN_NO_1 			1
#define GPIO_PIN_NO_2 			2
#define GPIO_PIN_NO_3 			3
#define GPIO_PIN_NO_4 			4
#define GPIO_PIN_NO_5 			5
#define GPIO_PIN_NO_6 			6
#define GPIO_PIN_NO_7 			7
#define GPIO_PIN_NO_8 			8
#define GPIO_PIN_NO_9 			9
#define GPIO_PIN_NO_10 			10
#define GPIO_PIN_NO_11 			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/*
 * GPIO pin possible modes
 * @GPIO_PIN_MODES
 */
#define GPIO_MODE_INPUT			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANLG			3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6


/*
 * GPIO pin possible output types
 * @GPIO_PIN_OTYP
 */
#define GPIO_OP_TYP_PP			0
#define GPIO_OP_TYP_OD			1


/*
 * GPIO pin possible output speeds
 * @GPIO_PIN_OSPEED
 */
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MED			1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3


/*
 * GPIO pin pull up pull down configuration
 * @GPIO_PIN_PUPD
 */
#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2



/*
 * GPIO Alt Function Modes
 * @GPIO_ALTFN_MODS
 */
#define GPIO_ALTFN_MOD_0		0
#define GPIO_ALTFN_MOD_1		1
#define GPIO_ALTFN_MOD_2		2
#define GPIO_ALTFN_MOD_3		3
#define GPIO_ALTFN_MOD_4		4
#define GPIO_ALTFN_MOD_5		5
#define GPIO_ALTFN_MOD_6		6
#define GPIO_ALTFN_MOD_7		7
#define GPIO_ALTFN_MOD_8		8
#define GPIO_ALTFN_MOD_9		9
#define GPIO_ALTFN_MOD_10		10
#define GPIO_ALTFN_MOD_11		11
#define GPIO_ALTFN_MOD_12		12
#define GPIO_ALTFN_MOD_13		13
#define GPIO_ALTFN_MOD_14		14
#define GPIO_ALTFN_MOD_15		15




/****************************************************************************
 * 							APIs supported by this driver
 *
 ****************************************************************************/

/*
 * Peripheral clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t __vo *const pGPIOx, uint8_t const EnorDi);

/*
 * Init and de-init
 */
void GPIO_Init(GPIO_Handle_t __vo *const pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t __vo *const pGPIOx);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_Handle_t __vo *const pGPIOHandle);
uint16_t GPIO_ReadFromInputPort(GPIO_Handle_t __vo *const pGPIOHandle);
void GPIO_WriteToOutputPin(GPIO_Handle_t __vo *const pGPIOHandle, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_Handle_t __vo *const pGPIOHandle, uint16_t const Value);
void GPIO_ToggleOutputPin(GPIO_Handle_t __vo *const pGPIOHandle);


/*
 * Interrupts
 */
void GPIO_IRQInterruptConfig(uint8_t const IRQNumber, uint8_t const EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t const PinNumber);


#endif /* INC_STM32F446XX_GPIO_H_ */
