/*
 * st32f446xx.h
 *
 *  Created on: Jan 16, 2023
 *      Author: Saurav Uprety
 */


#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
#define __vo volatile

/*
 * ******************************************************************************** *
* 			************** START: Poccessor Details **********************  *
 * ******************************************************************************** *
 *
 */

/*
 *ARM Cortex M4 Processer NVIC ISERx register addresses
 */
#define NVIC_ISER0				((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3				((__vo uint32_t*)0xE000E10C)
#define NVIC_ISER4				((__vo uint32_t*)0xE000E110)
#define NVIC_ISER5				((__vo uint32_t*)0xE000E114)
#define NVIC_ISER6				((__vo uint32_t*)0xE000E118)
#define NVIC_ISER7				((__vo uint32_t*)0xE000E11C)


/*
 *ARM Cortex M4 Processer NVIC ICERx register addresses
 */
#define NVIC_ICER0				((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2				((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3				((__vo uint32_t*)0xE000E18C)
#define NVIC_ICER4				((__vo uint32_t*)0xE000E190)
#define NVIC_ICER5				((__vo uint32_t*)0xE000E194)
#define NVIC_ICER6				((__vo uint32_t*)0xE000E198)
#define NVIC_ICER7				((__vo uint32_t*)0xE000E19C)

/*
 * NVIC Priority Register
 */
#define NVIC_PR_BASEADDR		((__vo uint32_t*)0xE000E400)


/*
 * IRQ Priority Macros
 */
#define NVIC_IRQ_PRI0			0
#define NVIC_IRQ_PRI1			1
#define NVIC_IRQ_PRI2			2
#define NVIC_IRQ_PRI3			3
#define NVIC_IRQ_PRI4			4
#define NVIC_IRQ_PRI5			5
#define NVIC_IRQ_PRI6			6
#define NVIC_IRQ_PRI7			7
#define NVIC_IRQ_PRI8			8
#define NVIC_IRQ_PRI9			9
#define NVIC_IRQ_PRI10			10
#define NVIC_IRQ_PRI11			11
#define NVIC_IRQ_PRI12			12
#define NVIC_IRQ_PRI13			13
#define NVIC_IRQ_PRI14			14
#define NVIC_IRQ_PRI15			15
#define NVIC_IRQ_PRI16			16
#define NVIC_IRQ_PRI17			17
#define NVIC_IRQ_PRI18			18


/*
 * ******************************************************************************** *
* 			************** END: Pocessor Details **********************  *
 * ******************************************************************************** *
 *
 */

/*
 * Base Address of Flash and SRAM
 */

#define FLASH_BASEADDR			0x08000000U
#define ROM_BASEADDR			0x1FFF0000U

#define SRAM1_BASEADDR			0x20000000U
#define SRAM2_BASEADDR			((SRAM1PERIPH_BASEADDR) + (0x1C00U))U
#define SRAM					SRAM1PERIPH_BASEADDR


/*
 * Base Address of AHBx and APBx bus peripherals
 */

#define PERIPH_BASEADDR			0x40000000U

#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U

#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50050000U
#define AHB3PERIPH_BASEADDR		0xA0000000U

/*
 * Base Address of peripherals on AHB1 bus
 */

//GPIO Base Addresses
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

/*
 * Base Address of peripherals on APB1 bus
 */
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR 			(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)

#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000)


/*
 * Base Address of peripherals on APB2 bus
 */
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR			(APB2PERIPH_BASEADDR + 0x3400)

#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)

#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800)


/*
 * ******************************************************************************** *
 * ************** Peripheral  Definition Structures **********************  *
 * ******************************************************************************** *
 *
 */

/*
 * GPIO register definition
 */
typedef struct
{								/*DESCRIPTION					OFFSET	*/
	__vo uint32_t MODER;		/*Port Mode						0x00	*/
	__vo uint32_t OTYPER;		/*Output Type					0x04	*/
	__vo uint32_t OSPEEDER;		/*Output Speed					0x08	*/
	__vo uint32_t PUPDR;		/*Pull Up/Pull Down				0x0C	*/
	__vo uint32_t IDR;			/*Input Data 					0x10	*/
	__vo uint32_t ODR;			/*Output Data					0x14	*/
	__vo uint32_t BSRR;			/*Bit Set/Reset					0x18	*/
	__vo uint32_t LCKR;			/*Config. Lock					0x1C	*/
	__vo uint32_t AFR[2];		/*Alternate Function Low 	[0]	0x20	*/
								/*Alternate Function High	[1]	0x24	*/
}GPIO_RegDef_t;


/*
 * RCC register definition
 */
typedef struct
{								/*DESCRIPTION				  	OFFSET	*/
	__vo uint32_t CR;			/*Clock Control 				0x00	*/
	__vo uint32_t PLLCFGR;		/*PLL Configuration  			0x04	*/
	__vo uint32_t CFGR;			/*Clock Configuration  			0x08	*/
	__vo uint32_t CIR;			/*Clock Interrupt 				0x0C	*/
	__vo uint32_t AHB1RSTR;		/*AHB1 Periph Reset 			0x10	*/
	__vo uint32_t AHB2RSTR;		/*AHB2 Periph Reset 			0x14	*/
	__vo uint32_t AHB3RSTR; 	/*AHB3 Periph Reset 			0x18	*/
	uint32_t RESEREVED0;		/*Reserved						0x1C	*/
	__vo uint32_t APB1RSTR;		/*APB1 Periph Reset 			0x20	*/
	__vo uint32_t APB2RSTR; 	/*APB2 Periph Reset 			0x24	*/
	uint32_t RESERVED1;			/*Reserved						0x28	*/
	uint32_t RESERVED2;			/*Reserved						0x2C	*/
	__vo uint32_t AHB1ENR;		/*AHB1 Clock Enable 			0x30	*/
	__vo uint32_t AHB2ENR;		/*AHB2 Clock Enable 			0x34	*/
	__vo uint32_t AHB3ENR;		/*AHB3 Clock Enable 			0x38	*/
	uint32_t RESERVED3;			/*Reserved						0x3C	*/
	__vo uint32_t APB1ENR;		/*APB1 Clock Enable 			0x40	*/
	__vo uint32_t APB2ENR;		/*APB2 Clock Enable 			0x44	*/
	uint32_t RESERVED4;			/*Reserved						0x48	*/
	uint32_t RESERVED5;			/*Reserved						0x4C	*/
	__vo uint32_t AHB1LPENR;	/*AHB1 LP Clock Enable 			0x50	*/
	__vo uint32_t AHB2LPENR;	/*AHB2 LP Clock Enable 			0x54	*/
	__vo uint32_t AHB3LPENR;	/*AHB3 LP Clock Enable 			0x58	*/
	uint32_t RESERVED6;			/*Reserved						0x5C	*/
	__vo uint32_t APB1LPENR;	/*APB1 LP Clock Enable 			0x60	*/
	__vo uint32_t APB2LPENR;	/*APB2 LP Clock Enable 			0x64	*/
	uint32_t RESERVED7;			/*Reserved						0x68	*/
	uint32_t RESERVED8;			/*Reserved						0x6C	*/
	__vo uint32_t BDCR;			/*Backup Domain Control 		0x70	*/
	__vo uint32_t CSR;			/*Clock Control & Status		0x74	*/
	uint32_t RESERVED9;			/*Reserved						0x78	*/
	uint32_t RESERVED10;		/*Reserved						0x7C	*/
	__vo uint32_t SSCGR;		/*Spread Spectrum Clock Gen.	0x80	*/
	__vo uint32_t PLLI2SCFGR;	/*PLLI2S Configuration			0x84	*/
	__vo uint32_t PLLSAICFGR;	/*PLL Configuration 			0x88	*/
	__vo uint32_t DCKCFGR;		/*Dedicated Clock Config. 1		0x8C	*/
	__vo uint32_t CKGATENR;		/*Clocks Gated Enable			0x90	*/
	__vo uint32_t DCKCFGR2;		/*Dedication Clock Config. 2	0x94	*/
}RCC_RegDef_t;


/*
 * EXTI register definition
 */
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;

}EXTI_RegDef_t;


/*
 * SYSCFG register definition
 */
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR [4];
	__vo uint32_t CMPCR;
	__vo uint32_t SYSCFG_CFGR;
}SYSCFG_RegDef_t;


/*
 * SPI register definition
 */
typedef struct
{
								/*DESCRIPTION					OFFSET*/
	__vo uint32_t CR1;			/*SPI control register 1 		0x00*/
	__vo uint32_t CR2;			/*SPI control register 2		0x04*/
	__vo uint32_t SR;			/*SPI status register			0x08*/
	__vo uint32_t DR;			/*SPI data register				0x0C*/
	__vo uint32_t CRCPR;		/*SPI CRC polynomial register	0x10*/
	__vo uint32_t RXCRCR;		/*SPI RX CRC register 			0x14*/
	__vo uint32_t TXCRCR;		/*SPI TX CRC register			0x18*/
	__vo uint32_t I2SCFGR;		/*SPI_I2S config. register		0x1C*/
	__vo uint32_t I2SPR;		/*SPI_I2S prescaler register	0x20*/
}SPI_RegDef_t;




/*
 * ******************************************************************************** *
 * ********************* Peripheral Definitions **********************************  *
 * ******************************************************************************** *
 *
 */
#define GPIOA					((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB					((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC					((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD					((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE					((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF					((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG					((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH					((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC						((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI					((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG					((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1					((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2					((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3					((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4					((SPI_RegDef_t*)SPI4_BASEADDR)



/*
 * ******************************************************************************** *
 * ********************* Peripheral Clock Macros **************************  *
 * ******************************************************************************** *
 *
 */
/*
 * Clock Enable Macros GPIOx Peripherals
 */
#define GPIOA_PCLK_EN()			(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()			(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()			(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()			(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()			(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()			(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()			(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()			(RCC->AHB1ENR |= (1 << 7))


/*
 * Clock Enable Macros I2Cx Peripherals
 */
#define I2C1_PCLK_EN()			(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()			(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()			(RCC->APB1ENR |= (1 << 23))


/*
 * Clock Enable Macros SPIx Peripherals
 */
#define SPI1_PCLK_EN()			(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()			(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()			(RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()			(RCC->APB2ENR |= (1 << 13))


/*
 * Clock Enable Macros USARTx Peripherals
 */
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()		(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()			(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()			(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()		(RCC->APB2ENR |= (1 << 5))


/*
 * Clock Enable Macros SYSCFG Peripheral
 */
#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

/*
 * Clock Disable Macros GPIOx Peripherals
 */
#define GPIOA_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()			(RCC->AHB1ENR &= ~(1 << 7))


/*
 * Clock Disable Macros I2Cx Peripherals
 */
#define I2C1_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 23))


/*
 * Clock Disable Macros SPIx Peripherals
 */
#define SPI1_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()			(RCC->APB2ENR &= ~(1 << 13))


/*
 * Clock Disable Macros USARTx Peripherals
 */
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()			(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock Enable Macros SYSCFG Peripheral
 */
#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))


/*
 * GPIO Peripheral reset macros
 */
#define GPIOA_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 0); RCC->AHB1RSTR &= ~(1 << 0);}while(0)
#define GPIOB_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 1); RCC->AHB1RSTR &= ~(1 << 1);}while(0)
#define GPIOC_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 2); RCC->AHB1RSTR &= ~(1 << 2);}while(0)
#define GPIOD_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 3); RCC->AHB1RSTR &= ~(1 << 3);}while(0)
#define GPIOE_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 4); RCC->AHB1RSTR &= ~(1 << 4);}while(0)
#define GPIOF_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 5); RCC->AHB1RSTR &= ~(1 << 5);}while(0)
#define GPIOG_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 6); RCC->AHB1RSTR &= ~(1 << 6);}while(0)
#define GPIOH_REG_RESET()		do{RCC->AHB1RSTR |= (1 << 7); RCC->AHB1RSTR &= ~(1 << 7);}while(0)


/*
 * SPI Peripheral reset macros
 */
#define SPI1_REG_RESET()		do{RCC->APB2RSTR |= (1 << 12); RCC->APB2RSTR &= ~(1 << 12);}while(0)
#define SPI2_REG_RESET()		do{RCC->APB1RSTR |= (1 << 14); RCC->APB1RSTR &= ~(1 << 14);}while(0)
#define SPI3_REG_RESET()		do{RCC->APB1RSTR |= (1 << 15); RCC->APB1RSTR &= ~(1 << 15);}while(0)
#define SPI4_REG_RESET()		do{RCC->APB2RSTR |= (1 << 13); RCC->APB2RSTR &= ~(1 << 12);}while(0)

/*
 * EXTI IRQ Numbers
 */
#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40


/*
 * Some generic macros
 */

#define ENABLE 					1
#define DISABLE					0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET
#define GPIO_PIN_HIGH			ENABLE
#define GPIO_PIN_LOW			DISABLE
#define FLAG_SET				SET
#define FLAG_RESET				RESET


/*
 * ******************************************************************************** *
 * *****************  Bitfield Mapping SPI Registers ***********************  *
 * ******************************************************************************** *
 *
 */
/*
 * SPI_CR1 bit positions
 */
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFRST			7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15

/*
 * SPI_CR2 bit positions
 */
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7

/*
 * SPI_SR bit positions
 */
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8





#include "stm32f446xx_gpio.h"
#include "stm32f446xx_spi.h"
#endif /* INC_STM32F446XX_H_ */

