//
// Created by oxford on 25.09.23.
//

#include "IMcu.h"


namespace hal::mcu {

    IMcu::IMcu(uint16_t pinsNbr):
    m_allPinsNbr(pinsNbr)
    {
    }

    eErrors IMcu::reservePin(uint16_t pinNo, eOwnership ownership)
    {
        if (pinNo > m_allPinsNbr)
        {
            return eErrors::eNotExist;
        }

        auto it = m_reservedPins.find(pinNo);

        if(it == m_reservedPins.end())
        {
            m_reservedPins.insert({pinNo, ownership});
        }
        else if(it->second == eOwnership::eUnique)
        {
            return eErrors::eAlreadyReserved;
        }

        return eErrors::eOk;
    }
} // hal::mcu