//
// Created by oxford on 27.09.23.
//
#pragma once

#include <cstdint>
#include "stm32l476xx.h"
#include "errors.h"

namespace hal::gpio {

    /// @brief Class representing an Input/Output port.
    ///
    /// The IPort class is used for managing an input/output port with a specified identifier.
    template<typename port_t>
    class IPort
    {
    public:

        /// @brief Constructor for the IPort class.
        ///
        /// @param portId The port identifier.
        
        IPort();
    protected:
        virtual error enableClk() = 0;
        virtual error disableClk() = 0;
    };

} //hal::gpio