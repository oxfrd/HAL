//
// Created by oxford on 19.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IMcu.h"

namespace hal::oneWire
{
    class IOneWire : public IResource
    {
    public:
        IOneWire() = default;
                
        virtual eError send(const uint8_t *buff, const uint16_t len) = 0;
        virtual eError get(uint8_t *buff, const uint16_t len) = 0;
        virtual eError reset() = 0;
        virtual eError selectDevice(const uint8_t rom[8]) = 0;
        virtual eError skipAdressing() = 0;
        virtual eError scanNetwork(uint8_t *p) = 0;

        std::pair<std::shared_ptr<IOneWire>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };
} //hal::oneWire