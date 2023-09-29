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
    class IPort
    {
    public:

        /// @brief Constructor for the IPort class.
        ///
        /// @param portId The port identifier.
        
        explicit IPort(GPIO_TypeDef *portId);
    private:
        volatile std::uint32_t *m_RCCEnReg;
        GPIO_TypeDef *m_regs;
        std::uint32_t m_id;
        error enableClk();
        error disableClk();


    };

} //hal::gpio