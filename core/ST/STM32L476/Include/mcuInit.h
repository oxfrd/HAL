//created by Oxfrd 8.11.2023
#pragma once

#include "IMcu.h"

namespace mcu{

enum class eMcuResources 
{
    eGPIO_E8,
    eGPIO_B2,
};

std::shared_ptr<hal::mcu::mcuManager> init();

}   //mcu