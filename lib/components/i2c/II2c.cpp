#include "II2c.h"

namespace hal::i2c
{
    std::pair<std::shared_ptr<II2c>, eError> II2c::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<II2c>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<II2c>(res)) 
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::i2c