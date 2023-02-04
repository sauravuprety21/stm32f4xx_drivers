/*
 * stm32f446xx_spi.c
 *
 *  Created on: Jan. 26, 2023
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
 *
 * @Note								-
 */



/*********************************************************************************
 * @fn									- SPI_GetFlagStatus
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 *
 * @Note								-
 */
uint8_t SPI_GetFlagStatus(SPI_Handle_t __vo *const pSPIHandle, uint32_t FlagName)
{
	if ((pSPIHandle->pSPIx->SR >> FlagName) & 1)
		return FLAG_SET;
	return FLAG_RESET;
}




/*********************************************************************************
 * @fn									- SPI_PeriClockControl
 *
 * @brief								- Enable or disable SPI peripheral clock in RCC
 * @param[in]							- Handle structure of SPI peripheral
 * @param[in]							- ENABLE (0) or DISABLE (1)
 *
 * @return								- void
 *
 * @Note								-
 */
void SPI_PeriClockControl(SPI_Handle_t __vo *const pSPIHandle, uint8_t const EnorDi)
{
	intptr_t spiBaseAddr = (intptr_t) (pSPIHandle->pSPIx);
	if(EnorDi)
	{
		switch (spiBaseAddr)
		{
			case SPI1_BASEADDR:
				SPI1_PCLK_EN();
				break;

			case SPI2_BASEADDR:
				SPI2_PCLK_EN();
				break;

			case SPI3_BASEADDR:
				SPI3_PCLK_EN();
				break;

			case SPI4_BASEADDR:
				SPI4_PCLK_EN();
				break;
		}
	} else {

		switch (spiBaseAddr)
		{
			case SPI1_BASEADDR:
				SPI1_PCLK_DI();
				break;

			case SPI2_BASEADDR:
				SPI2_PCLK_DI();
				break;

			case SPI3_BASEADDR:
				SPI3_PCLK_DI();
				break;

			case SPI4_BASEADDR:
				SPI4_PCLK_DI();
				break;
		}
	}

}


/*********************************************************************************
 * @fn									- SPI_Init
 *
 * @brief								- Init SPIx peripheral
 * @param[in]							- Handle structure to SPI peripheral
 * @param[in]							-
 *
 * @return								- void
 *
 * @Note								-
 */
void SPI_Init(SPI_Handle_t __vo *const pSPIHandle)
{
	uint32_t temp = 0;

	//1. Enable SPI peripheral clock
	SPI_PeriClockControl(pSPIHandle, ENABLE);

	//2. Configure SPI mode (master?slave?)
	temp |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;


	//2. SPI bus config.
	switch(pSPIHandle->SPIConfig.SPI_BusConfig)
	{
		case SPI_BUSCFG_FD:
			// BIDIMODE must be RESET
			temp &= ~(1 << SPI_CR1_BIDIMODE);
			break;

		case SPI_BUSCFG_HD:
			// BIDIMODE must be SET
			temp |= (1 << SPI_CR1_BIDIMODE);
			break;

		case SPI_BUSCFG_SMPLX_RX:
			// BIDIMODE must be RESET
			temp &= ~(1 << SPI_CR1_BIDIMODE);
			// RXONLY bit must be SET
			temp |= (1 << SPI_CR1_RXONLY);
			break;

		default:
			// SPI_BUSCFG_FD
			temp &= ~(1 << SPI_CR1_BIDIMODE);
	}
	//5. SPI Baud Rate config
	temp |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4. SPI Data Frame Format config
	temp |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//5. SPI ClockPhase config
	temp |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//6. SPI ClockPolarity config
	temp |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//7. SPI Software Slave Management config
	temp |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 |= temp;
}


/*********************************************************************************
 * @fn									- SPI_DeInit
 *
 * @brief								- DeInit SPIx peripheral
 * @param[in]							- Handle structure to SPI peripheral
 * @param[in]							-
 *
 * @return								- void
 *
 * @Note								-
 */
void SPI_DeInit(SPI_Handle_t __vo *const pSPIHandle)
{
	intptr_t spiBaseAddr = (intptr_t) (pSPIHandle->pSPIx);

	switch (spiBaseAddr)
	{
		case SPI1_BASEADDR:
			SPI1_REG_RESET();
			break;

		case SPI2_BASEADDR:
			SPI2_REG_RESET();
			break;

		case SPI3_BASEADDR:
			SPI3_REG_RESET();
			break;

		case SPI4_BASEADDR:
			SPI4_REG_RESET();
			break;
	}
}


/*********************************************************************************
 * @fn									- SPI_SendData
 *
 * @brief								- Send Data through SPI peripheral
 * @param[in]							- SPI handle structure
 * @param[in]							- Pointer to SPI Tx buffer
 * @param[in]							- Length of data to send
 *
 * @return								- void
 *
 * @Note								- Blocking (till all data of length LEN is sent)
 */
void SPI_SendData(SPI_Handle_t __vo *const pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	// While length not zero, keep writing to txBuffer
	while(Len > 0)
	{
		// While tX buffer not empty, wait (blocking)
		while(SPI_GetFlagStatus(pSPIHandle, SPI_TXE_FLAG) == FLAG_RESET);

		if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
		{
			pSPIHandle->pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;

		} else {
			// else (DDF == 8BITS)
			pSPIHandle->pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}


/*********************************************************************************
 * @fn									-
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_PeripheralControl(SPI_Handle_t __vo *const pSPIHandle, uint8_t EnorDi)
{
	if(EnorDi)
	{
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	} else
	{
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


/*********************************************************************************
 * @fn									-
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_SSIConfig(SPI_Handle_t __vo *const pSPIHandle, uint8_t EnorDi)
{
	if(EnorDi)
	{
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	} else
	{
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

