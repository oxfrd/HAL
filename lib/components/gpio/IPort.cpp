//
// Created by oxford on 27.09.23.
//

#include "IPort.h"

namespace hal::gpio {
    std::pair<std::shared_ptr<IPort>, eError> IPort::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IPort>, eError> retPair = {nullptr, eError::eFail};
        
        auto res = mcuMan->getResource(id);
        if (res != nullptr) 
        {
            retPair.first = std::dynamic_pointer_cast<hal::gpio::IPort>(res);
            retPair.second = eError::eOk;
        }
        
        return retPair; 
    }

}
