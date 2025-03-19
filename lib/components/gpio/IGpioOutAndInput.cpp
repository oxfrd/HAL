//
// Created by oxford on 01.10.23.
//

#include "IGpioOutAndInput.h"

namespace hal::gpio
{
    std::pair<std::shared_ptr<IGpioOutAndInput>, eError> IGpioOutAndInput::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IGpioOutAndInput>, eError> retPair = {nullptr, eError::eFail};
        
        auto res = mcuMan->getResource(id);
        if (res != nullptr) 
        {
            retPair.first = std::dynamic_pointer_cast<hal::gpio::IGpioOutAndInput>(res);
            retPair.second = eError::eOk;
        }
        return retPair;
    } 
} // namespace hal::gpio