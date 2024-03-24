//
// Created by oxford on 19.09.23.
//
#pragma once

#include "errors.h"
#include "IMcu.h"

namespace hal::interrupt
{
     /**
    * @brief Periodically interrupt interface.
    *
    * This class represents interface for periodically interrupt.
    * It defines interface for using it with hardware timer defined 
    * with ITimer interface.
    */
    class ITimeInterrupt : public IResource
    {
    public:
        ITimeInterrupt() = default;
        std::pair<std::shared_ptr<ITimeInterrupt>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError enable() = 0;
        virtual eError disable() = 0;
        virtual eError setPriority(std::uint32_t priority) = 0;
    };

} //hal::interrupt