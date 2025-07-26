#include "IEeprom.h"

namespace hal::eeprom
{
    std::pair<std::shared_ptr<IEeprom>, eError> IEeprom::getPtr(
        std::uint16_t id,
        std::shared_ptr<hal::mcu::mcuManager> mcuMan)
    {
        std::pair<std::shared_ptr<IEeprom>, eError> retPair = {nullptr, eError::eFail};
        auto res = mcuMan->getResource(id);
        if (auto uart = std::dynamic_pointer_cast<IEeprom>(res))
        {
            retPair.first = std::move(uart);
            retPair.second = eError::eOk;
        }

        return retPair;
    }
} // namespace hal::eeprom