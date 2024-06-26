//
// Created by oxford on 19.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IMcu.h"

namespace hal::uart
{
    typedef struct 
    {
        std::uint8_t pinId; 
        std::uint8_t portId;
    } pin_t;

    typedef struct
    {
        pin_t TX;
        pin_t RX;
    } pinOut_t;

    enum class eBaudrate
    {
        e9600 = 9600,
        e115200 = 115200,
    };

    class IUart : public IResource
    {
    public:
        IUart() = default;
        virtual eError send(uint8_t *sendMe, uint16_t len) = 0;
        virtual eError sendVector(std::vector<std::uint8_t> sendMe) = 0;

        virtual eError get(uint8_t *buff, uint16_t len) = 0;
        std::pair<std::shared_ptr<IUart>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError setBaudrate(eBaudrate speed) = 0;
    };
} //hal::uart