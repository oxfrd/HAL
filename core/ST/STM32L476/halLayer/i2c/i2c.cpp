//
// Created by oxford on 20.09.23.
//

#include "i2c.h"
#include <cassert>

std::array<circularBuffer*, cAllI2cInstances> mgTxBuff;
std::array<circularBuffer*, cAllI2cInstances> mgRxBuff;

namespace mcu::i2c
{
    using namespace hal::i2c;

    I2c::I2c(I2C_TypeDef *i2cRegs, std::shared_ptr<gpio::gpioAlternate> clkPin,
                std::shared_ptr<gpio::gpioAlternate> sdaPin,
                std::shared_ptr<interrupt::interrupt> interrupt,
                eSpeedMode speed = eSpeedMode::eStd):
    II2c(),
    mRegs(i2cRegs),
    mClkPin(clkPin),
    mSdaPin(sdaPin),
    mInterrupt(interrupt),
    mTxBuff(cTxBufferSize),
    mRxBuff(cRxBufferSize)
    {
        if(mRegs == nullptr)
        {
            assert(0);
        }

        if(mClkPin == nullptr)
        {
            assert(0);
        }

        if(mSdaPin == nullptr)
        {
            assert(0);
        }

        if(mInterrupt == nullptr)
        {
            assert(0);
        }

        enableClock(true);
        mClkPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eI2C1_2_3));
        mSdaPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eI2C1_2_3));
        setSpeed(speed);
        enableTransmit(true);
        // enableReceive(true);
        enableI2c(true);
        giveBuffer();
        mInterrupt->enable();
        enableRxInterrupts(true);
    }

    eError I2c::sendVector(std::vector<std::uint8_t> sendMe) 
    {
        for(const auto& sign : sendMe)
        {
            mTxBuff.put(sign);
        }
        enableTxInterrupts(true);
        return eError::eOk; 
    }

    eError I2c::send(uint8_t *buff, uint16_t len) 
    {
        for(uint8_t i = 0; i < len; i++)
        {
            mTxBuff.put(buff[i]);
        }
        enableTxInterrupts(true);
        return eError::eOk;
    }

    eError I2c::get(uint8_t *buff, uint16_t len) 
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

    eError I2c::setSpeed(eSpeedMode speed) 
    {
        mSpeedMode = speed;
        mRegs->BRR = SystemCoreClock / static_cast<std::uint32_t>(mSpeedMode);
        return eError::eOk;
    }

    eError I2c::enableClock(bool enable) 
    {
        if(enable)
        {
            RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
        }
        else
        {
            RCC->APB1ENR1 &= ~(RCC_APB1ENR1_I2C1EN);
        }
        return eError::eOk;
    }

    eError I2c::enableTransmit(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= I2C_CR1_TXIE;
        }
        else
        {
            mRegs->CR1 &= ~(I2C_CR1_TXIE);
        }
        return eError::eOk;
    }

    eError I2c::enableReceive(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= I2C_CR1_RXIE;
        }
        else
        {
            mRegs->CR1 &= ~(I2C_CR1_RXIE);
        }
        return eError::eOk;
    }

    eError I2c::enableI2c(bool enable) 
    { 
        if(enable)
        {
            mRegs->CR1 |= I2C_CR1_PE;
        }
        else
        {
            mRegs->CR1 &= ~(I2C_CR1_PE);
        }
        return eError::eOk;
    }

    eError I2c::giveBuffer() 
    {
        if (mRegs == I2C1)        
        {
            mgTxBuff.at(0) = &mTxBuff;
            mgRxBuff.at(0) = &mRxBuff;
            return eError::eOk;
        }
        else if (mRegs == I2C2)
        {
            mgTxBuff.at(1) = &mTxBuff;
            mgRxBuff.at(1) = &mRxBuff;
            return eError::eOk;
        }
        else if (mRegs == I2C3)
        {
            mgTxBuff.at(2) = &mTxBuff;
            mgRxBuff.at(2) = &mRxBuff;
            return eError::eOk;
        }
        
        return eError::eFail; 
    }

    eError I2c::enableTxInterrupts(bool enable) 
    {
        if(enable)
        {
            mRegs->CR1 |= I2C_CR1_TCIE;
        }
        else
        {
            mRegs->CR1 &= ~I2C_CR1_TCIE;
        }
        return eError::eOk; 
    }

    eError I2c::enableRxInterrupts(bool enable) 
    {
        if(enable)
        {
            mRegs->CR1 |= I2C_CR1_RXIE;
        }
        else
        {
            mRegs->CR1 &= ~I2C_CR1_RXIE;
        }

        return eError(); 
    }
} // I2c


std::uint8_t acc8{0};
bool isEmpty{false};

__attribute__((interrupt)) void I2C2_IRQHandler(void)
{
    // transmit
    if (I2C2->ISR & I2C_ISR_TXE)
    {
        if (mgTxBuff[1]->pop(&acc8))
        {
            I2C2->TDR = acc8;
        }
        else
        {
            I2C2->CR1 &= ~I2C_CR1_TCIE;
        }
    }

    // receive
    if (I2C2->ISR & I2C_ISR_RXNE) 
    {
        mgRxBuff[1]->put(I2C2->RDR);
    }
}
