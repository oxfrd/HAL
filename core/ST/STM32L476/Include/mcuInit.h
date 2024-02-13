//created by Oxfrd 8.11.2023
#pragma once

#include "IMcu.h"

#define HSE_VALUE 32768000
namespace mcu{

enum class eMcuResources 
{
    ePortB,
    ePortE,
    eGPIO_E8,
    eGPIO_B2,
};

std::shared_ptr<hal::mcu::mcuManager> init();

}   //mcu