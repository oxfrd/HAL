//
// Created by oxford on 27.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IMcu.h"

namespace hal::gpio {

    /** @brief Class representing an Input/Output port.
    *
    * The IPort class is used for managing an input/output port with a specified identifier. */
    class IPort : public IResource
    {
    public:
        IPort() = default;
        virtual eError enableClk() = 0;
        virtual eError disableClk() = 0;
        std::pair<std::shared_ptr<IPort>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
    };

} //hal::gpio