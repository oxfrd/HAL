//
// Created by oxford on 03.10.23.
//
#pragma once

#include <cstdint>
#include "errors.h"

namespace hal {
    /**
    * @brief General microcontroller interface.
    *
    * This class represents a general interface for a microcontroller device.
    * It defines basic operations for accessing the device and stores the device's identifier.
    *
    * @tparam devId_t Type of the device identifier.
    *   @IMPORTANT            !!! IMPORTANT !!!
    *   @IMPORTANT 0 must be defined as uninitialized in devId_t and cannot be used in another way!
    */
    template<typename devId_t>
    class IResource
    {
    public:
        /**
         * @brief Get the device identifier.
         *
         * This method returns the device identifier.
         *
         * @return Device identifier.
         */
        devId_t getDevId()
        {
            return m_id;
        }
    private:
        /**
         * @brief Device identifier.
         *
         * This field stores the device identifier.
         */
        devId_t m_id = static_cast<devId_t>(0);
    };
}