//
// Created by oxford on 20.09.23.
//

#include "uart.h"
#include <cassert>

std::array<circularBuffer*, 5> mgTxBuff;
std::array<circularBuffer*, 5> mgRxBuff;

namespace mcu::uart
{
    using namespace hal::uart;

    uart::uart(USART_TypeDef *uartRegs, std::shared_ptr<gpio::gpioAlternate> txPin, 
                std::shared_ptr<gpio::gpioAlternate> rxPin,
                std::shared_ptr<interrupt::interrupt> interrupt,
                eBaudrate baudrate):
    IUart(),
    mRegs(uartRegs),
    mTxPin(txPin),
    mRxPin(rxPin),
    mInterrupt(interrupt),
    mTxBuff(cTxBufferSize),
    mRxBuff(cRxBufferSize)
    {
        if(mRegs == nullptr)
        {
            assert(0);
        }

        if(mTxPin == nullptr)
        {
            assert(0);
        }

        if(mRxPin == nullptr)
        {
            assert(0);
        }

        if(mInterrupt == nullptr)
        {
            assert(0);
        }

        enableClock(true);
        setProperPinsFunctionality();
        setBaudrate(baudrate);
        enableTransmit(true);
        enableReceive(true);
        enableUART(true);
        giveBuffer();
        mInterrupt->enable();
        enableRxInterrupts(true);
    }

    void UART_SendChar(std::uint8_t c)
    {
        
    }

    eError uart::sendVector(std::vector<std::uint8_t> sendMe) 
    {
        for(const auto& sign : sendMe)
        {
            mTxBuff.put(sign);
        }
        enableTxInterrupts(true);
        return eError::eOk; 
    }

    eError uart::send(uint8_t *buff, uint16_t len) 
    {
        for(uint8_t i = 0; i < len; i++)
        {
            mTxBuff.put(buff[i]);
        }
        enableTxInterrupts(true);
        return eError::eOk;
    }

    eError uart::get(uint8_t *buff, uint16_t len) 
    {
        for(uint16_t i = 0; i<len; i++)
        {
            if (not mRxBuff.pop(buff))
            {
                return eError::eEmpty;
            }
        }
        return eError::eOk;
    }

    eError uart::setBaudrate(eBaudrate baudrate) 
    {
        mBaudRate = baudrate;
        mRegs->BRR = SystemCoreClock / static_cast<std::uint32_t>(mBaudRate);
        return eError::eOk;
    }

    eError uart::enableClock(bool enable) 
    {
        if(enable)
        {
            RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
        }
        else
        {
            RCC->APB1ENR1 &= ~(RCC_APB1ENR1_USART2EN);
        }
        return eError::eOk;
    }

    eError uart::enableTransmit(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= USART_CR1_TE;
        }
        else
        {
            mRegs->CR1 &= ~(USART_CR1_TE);
        }
        return eError::eOk;
    }

    eError uart::enableReceive(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= USART_CR1_RE;
        }
        else
        {
            mRegs->CR1 &= ~(USART_CR1_RE);
        }
        return eError::eOk;
    }

    eError uart::enableUART(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= USART_CR1_UE;
        }
        else
        {
            mRegs->CR1 &= ~(USART_CR1_UE);
        }
        return eError::eOk;
    }

    eError uart::giveBuffer() 
    {
        if (mRegs == USART1)        
        {
            mgTxBuff.at(0) = &mTxBuff;
            mgRxBuff.at(0) = &mRxBuff;
            return eError::eOk;
        }
        else if (mRegs == USART2)
        {
            mgTxBuff.at(1) = &mTxBuff;
            mgRxBuff.at(1) = &mRxBuff;
            return eError::eOk;
        }
        else if (mRegs == USART3)
        {
            mgTxBuff.at(2) = &mTxBuff;
            mgRxBuff.at(2) = &mRxBuff;
            return eError::eOk;
        }
        
        return eError::eFail; 
    }

    eError uart::enableTxInterrupts(bool enable) 
    {
        if(enable)
        {
            mRegs->CR1 |= USART_CR1_TCIE;
        }
        else
        {
            mRegs->CR1 &= ~USART_CR1_TCIE;
        }

        return eError(); 
    }

    eError uart::enableRxInterrupts(bool enable) 
    {
        if(enable)
        {
            mRegs->CR1 |= USART_CR1_RXNEIE;
        }
        else
        {
            mRegs->CR1 &= ~USART_CR1_RXNEIE;
        }

        return eError(); 
    }

    eError uart::setProperPinsFunctionality()
    {
        if( mRegs == USART1 ||
            mRegs == USART2 ||
            mRegs == USART3)
        {
            mTxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART1_2_3));
            mRxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART1_2_3));
        }
        else
        {
            mTxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART4_5_LPUART1));
            mRxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART4_5_LPUART1));
        }

        return eError::eOk;
    }
} // uart


std::uint8_t acc8{0};
bool isEmpty{false};

__attribute__((interrupt)) void USART2_IRQHandler(void)
{
    // transmit
    if (USART2->ISR & USART_ISR_TXE)
    {
        if (mgTxBuff[1]->pop(&acc8))
        {
            USART2->TDR = acc8;
        }
        else
        {
            USART2->CR1 &= ~USART_CR1_TCIE;
        }
    }

    // receive
    if (USART2->ISR & USART_ISR_RXNE) 
    {
        mgRxBuff[1]->put(USART2->RDR);
    }
}
