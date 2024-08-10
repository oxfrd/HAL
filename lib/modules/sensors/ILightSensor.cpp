#include "ILightSensor.h"

namespace hal::sensor
{
    std::pair<std::shared_ptr<ILightSensor>, eError> ILightSensor::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<ILightSensor>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<ILightSensor>(res)) 
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }
        return retPair; 
    } 
} // namespace hal::sensor