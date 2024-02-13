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
        e9600,
        e115200,
    };

    class IUart : public IResource
    {
    public:
        IUart() = default;
        virtual eError send() = 0;
        virtual eError get() = 0;
        std::pair<std::shared_ptr<IUart>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    protected:
        virtual eError setBaudrate(eBaudrate speed) = 0;
    private:
        eBaudrate m_baudrate;
    };
} //hal::uart