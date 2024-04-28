//
// Created by oxford on 28.04.24.
//
#pragma once

#include "errors.h"
#include "IPort.h"
#include "IGpio.h"
#include "IMcu.h"

namespace hal::gpio
{
    class IGpioAlternate : public IResource
    {
    public:
        IGpioAlternate() = default;
        std::pair<std::shared_ptr<IGpioAlternate>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} // namespace hal::gpio