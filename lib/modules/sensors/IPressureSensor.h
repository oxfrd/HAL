//
// Created by oxford on 02.07.24.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include <memory>

#include "IComponent.h"
#include <IMcu.h>

namespace hal::sensor
{
    class IPressureSensor : public IResource
    {
    public:
        IPressureSensor() = default;
        virtual eError enable(bool enable) = 0;
        virtual eError getValue(float *val) = 0;
        
        std::pair<std::shared_ptr<IPressureSensor>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} // namespace hal::sensor