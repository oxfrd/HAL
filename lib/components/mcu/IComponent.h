//
// Created by oxford on 03.10.23.
//
#pragma once

#include <cstdint>
#include "errors.h"
#include <vector>

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
        // std::uint16_t getDevId();

        /**
         * @brief Initialization of resource
         * 
         * @return  State of operation
         */
        // virtual error init();

        /**
         * @brief Uninitialization of resource
         * 
         * @return State of operation
         */
        // virtual error deInit();

        // hal::mcu::eOwnership g   etOwnership();
        // IResource(); 

    private:

        /**
         * @brief Device identifier.
         *
         * This field stores the device identifier.
         */
        // std::uint16_t m_id = 0;
        // hal::mcu::eOwnership m_ownership = mcu::eOwnership::eUnique;
        // std::uint8_t m_ownersNbr = 0;
    };
}