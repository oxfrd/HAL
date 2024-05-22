//
// Created by oxford on 20.09.23.
//

#include "uart.h"
#include <cassert>


namespace mcu::uart
{
    using namespace hal::uart;

    uart::uart(USART_TypeDef *uartRegs, std::shared_ptr<gpio::gpioAlternate> txPin, 
                std::shared_ptr<gpio::gpioAlternate> rxPin, eBaudrate baudrate):
    IUart(),
    m_regs(uartRegs),
    m_txPin(txPin),
    m_rxPin(rxPin)
    {
        if(m_regs == nullptr)
        {
            assert(0);
        }

        if(m_txPin == nullptr)
        {
            assert(0);
        }

        if(m_rxPin == nullptr)
        {
            assert(0);
        }
        enableClock(true);
        setProperPinsFunctionality();
        setBaudrate(baudrate);
        enableTransmit(true);
        enableReceive(true);
        enableUART(true);
    }

    void UART_SendChar(std::uint8_t c)
    {
        while (!(USART2->ISR & USART_ISR_TXE));
        USART2->TDR = c;
    }

    eError uart::send(std::vector<std::uint8_t> sendMe) 
    {
        for(const auto& sign : sendMe)
        {
            UART_SendChar(sign);
        }
        return eError::eOk; 
    }

    eError uart::get() { return eError::eFail; }

    eError uart::setBaudrate(eBaudrate baudrate) 
    {
        // // Choose alternate function AF7 for PA2 and PA3
        // GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk);
        // GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

        m_baudRate = baudrate;
        m_regs->BRR = SystemCoreClock / static_cast<std::uint32_t>(m_baudRate); // Assuming 9600 baud rate

        // Enable USART2 interrupts (if needed)
        // NVIC_EnableIRQ(USART2_IRQn);
        return eError::eFail;
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
            m_regs->CR1 |= USART_CR1_TE;
        }
        else
        {
            m_regs->CR1 &= ~(USART_CR1_TE);
        }
        return eError::eOk;
    }

    eError uart::enableReceive(bool enable) 
    { 
        if(enable)
        {
            m_regs->CR1 |= USART_CR1_RE;
        }
        else
        {
            m_regs->CR1 &= ~(USART_CR1_RE);
        }
        return eError::eOk;
    }

    eError uart::enableUART(bool enable) 
    { 
        if(enable)
        {
            m_regs->CR1 |= USART_CR1_UE;
        }
        else
        {
            m_regs->CR1 &= ~(USART_CR1_UE);
        }
        return eError::eOk;
    }
    
    eError uart::setProperPinsFunctionality()
    {
        if( m_regs == USART1 ||
            m_regs == USART2 ||
            m_regs == USART3)
        {
            m_txPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART1_2_3));
            m_rxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART1_2_3));
        }
        else
        {
            m_txPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART4_5_LPUART1));
            m_rxPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eUART4_5_LPUART1));
        }

        return eError::eOk;
    }
} // uart