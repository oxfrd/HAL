//
// Created by oxford on 27.09.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include "IMcu.h"

namespace hal::gpio 
{
    enum class eMode
    {
        eInput,
        eOutput,
        eAlternateFun,
        eAnalog,
    };

    /** @brief Class representing GPIO port.
    *
    * The IPort class is used for managing GPIO port with specified identifier. */
    template<class regType>
    class IPort : public IResource
    {
    public:
        IPort() = default;
        virtual eError enableClk() = 0;
        virtual eError disableClk() = 0;
        std::pair<std::shared_ptr<IPort>, eError> getPtr( 
            std::uint16_t id,
            std::shared_ptr<hal::mcu::mcuManager> mcuMan);
        virtual eError setPinMode(eMode mode, std::uint32_t pinId) = 0;
        virtual std::shared_ptr<regType> giveReg() = 0;
    };
} //namespace hal::gpio