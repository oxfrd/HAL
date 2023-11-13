//created by Oxfrd 8.11.2023
#pragma once
#include "IMcu.h"

namespace mcu::ST32L476{

enum class eMcuResources 
{
    eGPIO_E8,
    eGPIO_B2,
};

void init(hal::mcu::IMcu *mcuHandle);

}   //mcu::ST32L476