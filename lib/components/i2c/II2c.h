//
// Created by oxford on 19.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IMcu.h"

namespace hal::i2c
{
    enum class eSpeedMode
    {
        eStd,
        eFast,
    };

    class II2c : public IResource
    {
    public:
        II2c() = default;
        virtual eError send(std::uint8_t *sendMe, std::uint16_t len) = 0;
        virtual eError sendVector(std::vector<std::uint8_t> sendMe) = 0;

        virtual eError get(std::uint8_t *buff, std::uint16_t len) = 0;
        std::pair<std::shared_ptr<II2c>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError setSpeed(eSpeedMode speed) = 0;
    };
} //hal::i2c