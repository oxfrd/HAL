//created by Oxfrd 8.11.2023

#include <cassert>
#include <chrono>

#include "ITimer.h"

#include "mcuInit.h"
#include "gpioPort.h"
#include "gpioOutput.h"
#include "timer.h"
#include "timeInterrupt.h"

void checkErr(eError err)
{
    if(err != eError::eOk)
    {
        assert(0);
        while (1)
        {
            asm("NOP");
        }
    }
}

namespace mcu{

std::shared_ptr<hal::mcu::mcuManager> init()
{
    auto mcu = std::make_shared<hal::mcu::mcuManager>(hal::mcu::mcuManager());
    if (mcu == nullptr)
    {
        assert(0);
    }

    auto portE = std::make_shared<mcu::gpio::gpioPort>(mcu::gpio::gpioPort(4));
    auto err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::ePortE),std::move(portE));
    checkErr(err);
    auto getter = portE->getPtr(static_cast<uint16_t>(eMcuResources::ePortE),mcu);
    if (getter.second == eError::eOk)
    {
        portE = std::dynamic_pointer_cast<mcu::gpio::gpioPort>(getter.first);
    }

    auto portB = std::make_shared<mcu::gpio::gpioPort>(mcu::gpio::gpioPort(1));
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::ePortB),std::move(portB));
    checkErr(err);
    
    getter = portB->getPtr(static_cast<uint16_t>(eMcuResources::ePortB),mcu);
    if (getter.second == eError::eOk)
    {
        portB = std::dynamic_pointer_cast<mcu::gpio::gpioPort>(getter.first);
    }


    auto gpio = std::make_shared<gpio::gpioOutput>(8, portE, GPIOE);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_E8),std::move(gpio));
    checkErr(err);

    gpio = std::make_shared<gpio::gpioOutput>(2, portB, GPIOB);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eGPIO_B2), std::move(gpio));
    checkErr(err);

    // hal::timer::period_t timing(5.0);
    auto timer = std::make_shared<timer::countingTimer>(TIM2);//, timing);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eTimer2), std::move(timer));
    checkErr(err);


    std::shared_ptr<timer::countingTimer> tim2{nullptr};
    {
        auto timGetter = tim2->getPtr(static_cast<uint16_t>(eMcuResources::eTimer2), mcu);
        if (timGetter.second == eError::eOk)
        {
            tim2 = std::dynamic_pointer_cast<timer::countingTimer>(timGetter.first);
        }
    }

    auto interrupt = std::make_shared<interrupt::timeInterrupt>(TIM2_IRQn, tim2);
    err = mcu->reserveResource(static_cast<std::uint16_t>(eMcuResources::eIntTim2), std::move(interrupt));
    checkErr(err);

    return std::move(mcu);
}

}   //mcu
