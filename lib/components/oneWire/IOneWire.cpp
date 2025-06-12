#include "IOneWire.h"

namespace hal::oneWire
{
    std::pair<std::shared_ptr<IOneWire>, eError> IOneWire::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IOneWire>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<IOneWire>(res)) 
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    } 
} //hal::oneWire