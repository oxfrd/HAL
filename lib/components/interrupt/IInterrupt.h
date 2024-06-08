//
// Created by oxford on 03.06.24.
//
#pragma once

#include "errors.h"
#include "IMcu.h"

namespace hal::interrupt
{
     /**
    * @brief Periodically interrupt interface.
    *
    * This class represents interface for interrupt.
    * It defines interface for using it in general.
    */
    class IInterrupt : public IResource
    {
    public:
        IInterrupt() = default;
        std::pair<std::shared_ptr<IInterrupt>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError enable() = 0;
        virtual eError disable() = 0;
        virtual eError setPriority(std::uint32_t priority) = 0;
    };

} //hal::interrupt