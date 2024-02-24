//
// Created by oxford on 19.09.23.
//
#pragma once

#include "errors.h"
#include "IMcu.h"
#include "chrono"

namespace hal::timer
{
    using period_t = std::chrono::duration<double>;
     /**
    * @brief General microcontroller interface.
    *
    * This class represents interface for a microcontroller timer.
    * It defines interface for using hardware or software timers it doesnt matter .
    */
    class ITimer : public IResource
    {
    public:
        ITimer() = default;
        std::pair<std::shared_ptr<ITimer>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError setPeriod(period_t period) = 0;
        virtual eError enable() = 0;
        virtual eError disable() = 0;
        virtual eError enableClk() = 0;

    };

} //hal::timer