//
// Created by oxford on 19.03.25.
//
#pragma once

#include "stm32l476xx.h"
#include "IOneWire.h"
#include "IDelay.h"
#include "interrupt.h"
#include "gpioOutAndInput.h"
#include "circularBuffer.h"

namespace mcu::oneWire {

    using namespace hal::oneWire;
    
    /**
     * @brief Class holding functionality of one wire. 
     */
    class oneWire : public IOneWire
    {
    public:
        explicit oneWire(std::shared_ptr<gpio::gpioOutAndInput> pin, std::shared_ptr<hal::delay::IDelay> delay);
    
        eError get(uint8_t *buff, const uint16_t len) override final;
        eError send(const uint8_t *buff, const uint16_t len) override final;
        eError reset() override final;
        eError selectDevice(const uint8_t rom[8]) override final;
        eError skipAdressing() override final;
    
    private:
        static constexpr std::uint8_t cRetriesDuringReset{20};
        std::shared_ptr<gpio::gpioOutAndInput> mPin{nullptr}; 
        std::shared_ptr<hal::delay::IDelay> mDelay{nullptr};

        bool readBit();
        uint8_t readByte();
        eError writeBit(bool bit);
        eError writeByte(uint8_t byte, bool powerOff = true);



    



        eError setSpeed(eSpeedMode speed) override;
        eError send(std::uint8_t addr, uint8_t *sendMe, uint16_t len) override;
        eError sendVector(std::uint8_t addr, std::vector<std::uint8_t> sendMe) override; 
        eError get(std::uint8_t addr, std::uint8_t reg, uint8_t *buff, uint16_t len) override;
    private:
        static constexpr size_t cTxBufferSize{1000};
        static constexpr size_t cRxBufferSize{1000};
        static constexpr std::uint16_t cLoopReplaysLimit{1000};

        I2C_TypeDef *mRegs;
        eSpeedMode mSpeedMode;
        
        eError enableI2c(bool enable);
        eError enableClock(bool enable);
        eError setProperPinsFunctionality();
        eError enableTransmit(bool enable);
        eError enableReceive(bool enable);
        eError enableTxInterrupts(bool enable);
        eError enableRxInterrupts(bool enable); 
        eError giveBuffer();
        eError waitForFlag(uint32_t flag, bool notNegate);
    };
} // mcu::i2c
