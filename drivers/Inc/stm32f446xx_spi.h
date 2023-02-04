/*
 * stmf446xx_spi.h
 *
 *  Created on: Jan. 26, 2023
 *      Author: Saurav Uprety
 */

#ifndef INC_STM32F446XX_SPI_H_
#define INC_STM32F446XX_SPI_H_

/*
 * Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;				/*|< Possible values from @SPI_DeviceMode*/
	uint8_t SPI_BusConfig;				/*|< Possible values from @SPI_BusConfig*/
	uint8_t SPI_SclkSpeed;				/*|< Possible values from @SPI_SclkSpeed*/
	uint8_t SPI_DFF;					/*|< Possible values from @SPI_DFF*/
	uint8_t SPI_CPHA;					/*|< Possible values from @SPI_CPHA*/
	uint8_t SPI_CPOL;					/*|< Possible values from @SPI_CPOL*/
	uint8_t SPI_SSM;					/*|< Possible values from @SPI_SSM*/
}SPI_Config_t;


/*
 * Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t *pSPIx;					/*!<Holds BASE_ADDR of SPIx peripheral>*/
	SPI_Config_t SPIConfig;
}SPI_Handle_t;


/*
 * @SPI_DeviceMode
 */
#define SPI_DEVMOD_MSTR 		1
#define SPI_DEVMOD_SLVE			0


/*
 * @SPI_BusConfig
 */
#define SPI_BUSCFG_FD			1
#define SPI_BUSCFG_HD			2
#define SPI_BUSCFG_SMPLX_RX		3


/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_DIV2			0
#define SPI_SCLK_DIV4			1
#define SPI_SCLK_DIV8			2
#define SPI_SCLK_DIV16			3
#define SPI_SCLK_DIV32			4
#define SPI_SCLK_DIV64			5
#define SPI_SCLK_DIV128			6
#define SPI_SCLK_DIV256			8
#define SPI_SCLK_MAX			SPI_SCLK_DIV2
#define SPI_SLCK_MIN			SPI_SCLK_DIV256

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS			0
#define	SPI_DFF_16BITS			1


/*
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH			1
#define SPI_CPOL_LOW			0


/*
 * @SPI_CPHA
 */
#define SPI_CPHA_LOW			0
#define SPI_CPHA_HIGH			1


/*
 * @SPI_SSM
 */
#define SPI_SSM_DI				0
#define SPI_SSM_EN				1

/****************************************************************************
 * 							APIs supported by this driver
 *
 ****************************************************************************/

uint8_t SPI_GetFlagStatus(SPI_Handle_t __vo *const pSPIHandle, uint32_t FlagName);

/*
 * Peripheral clock setup
 */
void SPI_PeriClockControl(SPI_Handle_t __vo *const pSPIHandle, uint8_t const EnorDi);


/*
 * Init and de-init
 */
void SPI_Init(SPI_Handle_t __vo *const pSPIHandle);
void SPI_DeInit(SPI_Handle_t __vo *const pSPIHandle);


/*
 * Data send and receive
 */
void SPI_SendData(SPI_Handle_t __vo *const pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Handle_t __vo *const pSPIhandle, uint8_t pRxBuffer, uint32_t Len);


/*
 * IRQ configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t const IRQNumber, uint8_t const EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t __vo *const pSPIhandle);


/*
 * Other peripheral control APIs
 */
void SPI_PeripheralControl(SPI_Handle_t __vo *const pSPIHandle, uint8_t EnorDi);
void SPI_SSIConfig(SPI_Handle_t __vo *const pSPIHandle, uint8_t EnorDi);


/*
 * SPI Flags (Status Register)
 */
#define SPI_RXNE_FLAG			0
#define SPI_TXE_FLAG			1
#define SPI_CHSIDE_FLAG			2
#define SPI_UDR_FLAG			3
#define SPI_CRCERR_FLAG			4
#define SPI_MODF_FLAG			5
#define SPI_OVR_FLAG			6
#define SPI_BSY_FLAG			7
#define SPI_FRE_FLAG			8



#endif /* INC_STM32F446XX_SPI_H_ */
