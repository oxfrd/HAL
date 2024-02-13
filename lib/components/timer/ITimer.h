//
// Created by oxford on 19.09.23.
//
#pragma once

#include "errors.h"
#include "IMcu.h"
#include "chrono"

namespace hal::uart
{
    using std::chrono::duration<double> period_t;
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
    private:
        virtual setPeriod(period_t period) = 0;
    };

} //hal::uart