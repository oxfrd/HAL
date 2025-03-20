//
// Created by oxford on 20.03.25.
//
#pragma once

#include "errors.h"
#include "IMcu.h"
#include "chrono"

namespace hal::delay
{
    using period_t = std::chrono::duration<double>;

     /**
    * @brief General microcontroller interface.
    *
    * This class represents interface for a delay.
    * It defines interface for using hardware or software delay it doesnt matter.
    */
    class IDelay : public IResource
    {
    public:
        IDelay() = default;
        std::pair<std::shared_ptr<IDelay>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);

        virtual eError delayUs(std::chrono::microseconds us) = 0;
        virtual eError delayMs(std::chrono::milliseconds ms) = 0;
    };

} //hal::timer