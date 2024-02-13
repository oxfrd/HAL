//
// Created by oxford on 20.09.23.
//
#pragma once

#include "IUart.h"
#include "stm32l476xx.h"

namespace mcu::uart {

    using namespace hal::uart;
    
    /**
     * @brief Class holding functionality of uart output. 
     */
    class uart : public hal::uart::IUart //<GPIO_TypeDef>
    {
    public:
        explicit uart(std::uint8_t pinId, uint8_t portId);
        // eError deInit() override;
        // eError init() override;
    protected:
        eError setBaudrate(eBaudrate speed) override;
    private:

    };
} // mcu::uart
