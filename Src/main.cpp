//
// Created by oxford on 30.05.23.
//
#include <vector>
#include "stm32l476xx.h"
#include "gpioOutput.h"
#include "IComponent.h"
#include "mcuInit.h"
#include "main.h"
#include "timeInterrupt.h"
#include "delay.h"
#include <gpioInput.h>

static void errHandler()
{
    while(1)
    {
        asm("NOP");
    }
}

// static void func(std::shared_ptr<hal::mcu::mcuManager> x)
// {
//     using namespace mcu;

//     std::shared_ptr<gpio::gpioOutput> led{nullptr};
//     auto getter = led->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2), x);
//     if (getter.second == eError::eOk)
//     {
//         led = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
//     }

//     led->toggle();
//     delayMe(40);
//     led->toggle();
//     delayMe(40);
//     led->toggle();
//     delayMe(40);
// }

int main()
{
    using namespace mcu;
    auto mcu = init();
    
    std::shared_ptr<gpio::gpioOutput> ledRed{nullptr};
    {
        auto getter = ledRed->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_B2),mcu);
        if (getter.second == eError::eOk)
        {
            ledRed = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
        } else { errHandler();}
    }

    std::shared_ptr<gpio::gpioOutput> ledGreen{nullptr};
    {
        auto getter = ledGreen->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_E8),mcu);
        if (getter.second == eError::eOk)
        {
            ledGreen = std::dynamic_pointer_cast<gpio::gpioOutput>(getter.first);
        } else { errHandler();}
    }
    
    std::shared_ptr<gpio::gpioInput> A0{nullptr};
    {
        auto getter = A0->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_A0),mcu);
        if (getter.second == eError::eOk)
        {
            A0 = std::dynamic_pointer_cast<gpio::gpioInput>(getter.first);
        } else { errHandler();}
    }

    std::shared_ptr<gpio::gpioInput> A1{nullptr};
    {
        auto getter = A1->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_A1),mcu);
        if (getter.second == eError::eOk)
        {
            A1 = std::dynamic_pointer_cast<gpio::gpioInput>(getter.first);
        } else { errHandler();}
    }
    
    std::shared_ptr<gpio::gpioInput> A2{nullptr};
    {
        auto getter = A2->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_A2),mcu);
        if (getter.second == eError::eOk)
        {
            A2 = std::dynamic_pointer_cast<gpio::gpioInput>(getter.first);
        } else { errHandler();}
    }
    
    std::shared_ptr<gpio::gpioInput> A3{nullptr};
    {
        auto getter = A3->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_A3),mcu);
        if (getter.second == eError::eOk)
        {
            A3 = std::dynamic_pointer_cast<gpio::gpioInput>(getter.first);
        } else { errHandler();}
    }
    
    std::shared_ptr<gpio::gpioInput> A5{nullptr};
    {
        auto getter = A5->getPtr(static_cast<uint16_t>(eMcuResources::eGPIO_A5),mcu);
        if (getter.second == eError::eOk)
        {
            A5 = std::dynamic_pointer_cast<gpio::gpioInput>(getter.first);
        } else { errHandler();}
    }
    std::shared_ptr<interrupt::timeInterrupt> interrupt{nullptr};
    {
        auto getter = interrupt->getPtr(static_cast<uint16_t>(eMcuResources::eIntTim2),mcu);
        if (getter.second == eError::eOk)
        {
            interrupt = std::dynamic_pointer_cast<interrupt::timeInterrupt>(getter.first);
        } else { errHandler();}
    }

    interrupt->enable();

    auto a0State = false;
    auto a1State = false;
    auto a2State = false;
    auto a3State = false;
    auto a5State = false;
    
    while (true)
    {
        a0State = A0->getState();
        a1State = A1->getState();
        a2State = A2->getState();
        a3State = A3->getState();
        a5State = A5->getState();
        
        while(a0State || a1State || a2State || a3State || a5State)
        {
            constexpr std::uint32_t x{500};
            ledRed->toggle();
            ledGreen->toggle();
            delayMe(x);
            break;
        }
    }
    return 0;
}