//
// Created by oxford on 19.03.25.
//
#pragma once

#include "stm32l476xx.h"
#include "IOneWire.h"
#include "IDelay.h"
#include "interrupt.h"
#include "gpioOutAndInput.h"

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
    };
} // mcu::oneWire
