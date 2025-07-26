//
// Created by oxford on 15.06.25.
//
#pragma once

#include <cstdint>
#include "errors.h"

#include "IComponent.h"
#include <IMcu.h>

namespace hal::eeprom
{
    class IEeprom : public IResource
    {
    public:
        IEeprom() = default;
        virtual eError read(uint32_t offset, uint8_t *data , size_t length) = 0;
        virtual eError write(uint32_t offset, uint8_t *data , size_t length) = 0;
        virtual eError getAddress(uint32_t *address) = 0;
        virtual eError getSize(uint32_t *size) = 0;
        
        std::pair<std::shared_ptr<IEeprom>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} // namespace hal::sensor