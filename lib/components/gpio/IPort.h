//
// Created by oxford on 27.09.23.
//
#pragma once

#include <cstdint>
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
        virtual eError enableClk() = 0;
        virtual eError disableClk() = 0;
    };

    template<typename port_t>
    IPort<port_t>::IPort() {

    }

} //hal::gpio