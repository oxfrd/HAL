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
    class ILightSensor : public IResource
    {
    public:
        ILightSensor() = default;
        virtual eError enable() = 0;
        virtual eError getValue(float *val) = 0;
        
        std::pair<std::shared_ptr<ILightSensor>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} // namespace hal::sensor