//
// Created by oxford on 19.03.25.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include <memory>

#include "IComponent.h"
#include <IMcu.h>

namespace hal::sensor
{
    class ITemperatureSensor : public IResource
    {
    public:
        ITemperatureSensor() = default;
        virtual eError enable(bool enable) = 0;
        virtual eError getTemperature(float *val) = 0;
        virtual eError getAddress(uint64_t *address) = 0;
        
        std::pair<std::shared_ptr<ITemperatureSensor>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} // namespace hal::sensor