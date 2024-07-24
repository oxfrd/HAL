//
// Created by oxford on 20.09.23.
//

#include "i2c.h"
#include <cassert>

std::array<circularBuffer*, mcu::i2c::cAllI2cInstances> mgTxBuff;
std::array<circularBuffer*, mcu::i2c::cAllI2cInstances> mgRxBuff;

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

        RCC->APB1RSTR1 |= RCC_APB1RSTR1_I2C1RST;
        RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_I2C1RST;
        enableI2c(false);
        enableClock(true);
        mClkPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eI2C1_2_3));
        mSdaPin->setFunctionality(static_cast<std::uint32_t>(mcu::gpio::eFunctionality::eI2C1_2_3));
        setSpeed(speed);
        enableTransmit(true);
        // enableReceive(true);
        giveBuffer();
        mInterrupt->enable();
        enableRxInterrupts(true);
        enableI2c(true);
    }

    eError I2c::sendVector(std::uint8_t addr, std::vector<std::uint8_t> sendMe) 
    {
        for(const auto& sign : sendMe)
        {
            mTxBuff.put(sign);
        }
        enableTxInterrupts(true);
        return eError::eOk; 
    }

    eError I2c::send(std::uint8_t addr, uint8_t *buff, uint16_t len) 
    {
        mRegs->CR2 = (addr << I2C_CR2_SADD_Pos) & I2C_CR2_SADD;
        mRegs->CR2 |= (len << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES;
        mRegs->CR2 |= I2C_CR2_START;20

        for (int i = 0; i < len; i++ )
        {
            mRegs->TXDR = buff[i];
            while (!(mRegs->ISR & I2C_ISR_TXIS));
        }

        // // Czekanie na TXIS
        // while (!(mRegs->ISR & I2C_ISR_TXIS));

        // // Wysyłanie danych
        // mRegs->TXDR = buff[1];

        // // Czekanie na zakończenie transmisji (TC - Transfer Complete)
        // while (!(mRegs->ISR & I2C_ISR_TC));

        // Stop komunikacji
        mRegs->CR2 |= I2C_CR2_STOP;

        // Czekanie na STOPF (Stop Detection Flag)
        while (!(mRegs->ISR & I2C_ISR_STOPF));

        // Wyczyść flagę STOPF
        mRegs->ICR |= I2C_ICR_STOPCF;

/**********************************************/
        // mRegs->CR2 |= I2C_CR2_START;
        // while (!(mRegs->SR1 & I2C_SR1_SB));

        // // Adres urządzenia (z bitem Write)
        // mRegs->DR = deviceAddress << 1;
        // while (!(mRegs->SR1 & I2C_SR1_ADDR));
        // (void)mRegs->SR2;




        // mRegs->TXDR = (addr << 1);
        // while (!(mRegs->SR1 & I2C_SR1_ADDR));
        // for(uint8_t i = 0; i < len; i++)
        // {

        //     // mTxBuff.put(buff[i]);
        // }
        // enableTxInterrupts(true);
        return eError::eOk;
    }

    eError I2c::get(std::uint8_t addr, std::uint8_t *buff, std::uint16_t len) 
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
        constexpr uint32_t cNanoseconds{1000000000};
        constexpr uint32_t cKilo{1000};
        mSpeedMode = speed;
        uint32_t tClkNs = cNanoseconds/SystemCoreClock;
        uint32_t tI2cNs = cNanoseconds/(static_cast<uint32_t>(mSpeedMode) * cKilo);
        uint32_t scl = (tClkNs/tI2cNs) - 1;
        
        mRegs->TIMINGR = (0 << I2C_TIMINGR_PRESC_Pos)   |
                         (2 << I2C_TIMINGR_SDADEL_Pos)  |
                         (4 << I2C_TIMINGR_SCLDEL_Pos)  |
                         (scl << I2C_TIMINGR_SCLH_Pos)  |
                         (scl << I2C_TIMINGR_SCLL_Pos)  ;
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

        return eError::eOk;
    }
} // I2c


std::uint8_t acc8{0};
bool isEmpty{false};

// __attribute__((interrupt)) void I2C1_IRQHandler(void)
// {
//     // transmit
//     if (I2C1->ISR & I2C_ISR_TXE)
//     {
//         if (mgTxBuff[0]->pop(&acc8))
//         {
//             I2C1->TXDR = acc8;
//         }
//         else
//         {
//             I2C1->CR1 &= ~I2C_CR1_TCIE;
//         }
//     }

//     // receive
//     if (I2C1->ISR & I2C_ISR_RXNE) 
//     {
//         mgRxBuff[0]->put(I2C1->RXDR);
//     }
// }
