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
			pSPIHandle->pSPIx->DR = *(uint16_t*)pTxBuffer;
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
 * @fn									- SPI_ReceiveData
 *
 * @brief								- Recieve Data through SPI peripheral
 * @param[in]							- SPI handle structure
 * @param[in]							- Pointer to SPI Rx buffer
 * @param[in]							- Length of data to send
 *
 * @return								-
 *
 * @Note								- Blocking (till all data of length LEN is sent)
 */
void SPI_ReceiveData(SPI_Handle_t __vo *const pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	while (Len > 0)
	{
//		while(SPI_GetFlagStatus(pSPIHandle, SPI_RXNE_FLAG));		// Wait until Rx buffer full

		if(pSPIHandle->SPIConfig.SPI_DFF == SPI_DFF_16BITS)
		{
			*(uint16_t*)pRxBuffer = pSPIHandle->pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;

		} else {
			// else (DDF == 8BITS)
			*pRxBuffer = pSPIHandle->pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}



/*********************************************************************************
 * @fn									- SPI_SendData_IT
 *
 * @brief								- Setup SPI Handle strucutre for data send through interrupt mode
 * 										  This requires storing bufferaddress and within the global SPIHandle struct.
 * 										  so that it can be accessesed by the interrupt handler.
 *
 * @param[in]							- Pointer to SPI handle structure
 * @param[in]							- Pointer to SPI Rx buffer
 * @param[in]							- Length of data to send
 *
 * @return								- void
 *
 * @Note								- Non-blocking as code exec. not halted on wait for TXE flag.
 */
uint8_t SPI_SendData_IT(SPI_Handle_t __vo *const pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->TxState;
	if (state != SPI_BSY_TX)
	{
		/* 1. Save Tx buffer address and length to SPIHandle for global access */
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;

		/* 2. Mark SPI status for the pSPIHandle structure as busy, to safegaurd from access else where on the code*/
		pSPIHandle->TxState = SPI_BSY_TX;

		/* 3. Enable pSPIx->CR2::TXEIE bit to get interrupt when TXE bit set in pSPIx->SR */
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
	}
	return state;
}



/*********************************************************************************
 * @fn									- SPI_SendData_IT
 *
 * @brief								-
 * @param[in]							- Pointer to SPI handle structure
 * @param[in]							- Pointer to SPI Rx buffer
 * @param[in]							- Length of data to send
 *
 * @return								- void
 *
 * @Note								-
 */
uint8_t SPI_ReceiveData_IT(SPI_Handle_t __vo *const pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;
	if (state != SPI_BSY_RX)
	{
		/* 1. Save Tx buffer address and length to SPIHandle for global access */
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;

		/* 2. Mark SPI status for the pSPIHandle structure as busy, to safegaurd from access else where on the code*/
		pSPIHandle->RxState = SPI_BSY_RX;

		/* 3. Enable pSPIx->CR2::TXEIE bit to get interrupt when TXE bit set in pSPIx->SR */
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
	}
	return state;
}




/*********************************************************************************
 * @fn									- SPI_IRQInterruptConfig
 *
 * @brief								- Enable or Disable interrupt request  in NVIC
 * @param[in]							- Interrupt Request number
 * @param[in]							- Enable or Disable
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_IRQInterruptConfig(uint8_t const IRQNumber, uint8_t const EnorDi)
{
	uint8_t temp1 = IRQNumber / 32;
	uint8_t temp2 = IRQNumber % 32;

	if(EnorDi)			//ENABLE
	// Set corresponding bit for the right INTERRUPT SET ENABLE REGISTER
	{
		switch (temp1)
		{
			case 0:
				*NVIC_ISER0 |= (1 << temp2);
				break;
			case 1:
				*NVIC_ISER1 |= (1 << temp2);
				break;
			case 2:
				*NVIC_ISER2 |= (1 << temp2);
				break;
		}
	} else {	//DISABLE
		// Set corresponding bit for the right INTERRUPT CLEAR ENABLE REGISTER
		switch (temp1)
		{
			case 0:
				*NVIC_ICER0 |= (1 << temp2);
				break;
			case 1:
				*NVIC_ICER1 |= (1 << temp2);
				break;
			case 2:
				*NVIC_ICER2 |= (1 << temp2);
				break;
		}
	}
}



/*********************************************************************************
 * @fn									- SPI_IRQPriorityConfig
 *
 * @brief								- Configure the IRQ priority number in NVIC
 * @param[in]							- IRQ number
 * @param[in]							- IRQ priority
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t temp1 = IRQNumber / 4;
	uint8_t temp2 = IRQNumber % 4;

	*(NVIC_PR_BASEADDR + 4*temp1) &= ~(0xFF << (8 * temp2 + 4));
	*(NVIC_PR_BASEADDR + 4*temp1) |= (IRQPriority << (8 * temp2 + 4));
}



/*********************************************************************************
 * @fn									- SPI_IRQHandling
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_IRQHandling(SPI_Handle_t __vo *const pSPIhandle)
{

}





/*********************************************************************************
 * @fn									- SPI_PeripheralControl
 *
 * @brief								- Enable or Disable the SPI perih using pSPIx->CR1 SPE bit
 * @param[in]							- pointer to SPI handle structure
 * @param[in]							- ENABLE or DISABLE
 *
 * @return								- None
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
 * @fn									- SPI_SSIConfig
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



/*********************************************************************************
 * @fn									- SPI_SSOEConfig
 *
 * @brief								-
 * @param[in]							-
 * @param[in]							-
 *
 * @return								-
 *
 * @Note								-
 */
void SPI_SSOEConfig(SPI_Handle_t __vo *const pSPIHandle, uint8_t EnorDi)
{
	if(EnorDi)
	{
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	} else
	{
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR2_SSOE);
	}
}

