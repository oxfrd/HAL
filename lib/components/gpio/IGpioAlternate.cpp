//
// Created by oxford on 28.04.24.
//

#include "IGpioAlternate.h"

namespace hal::gpio
{
    std::pair<std::shared_ptr<IGpioAlternate>, eError> IGpioAlternate::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IGpioAlternate>, eError> retPair = {nullptr, eError::eFail};
        
        auto res = mcuMan->getResource(id);
        if (res != nullptr)
        {
            retPair.first = std::dynamic_pointer_cast<hal::gpio::IGpioAlternate>(res);
            retPair.second = eError::eOk;
        }
        return retPair;
    }
} // namespace hal::gpio