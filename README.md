# HAL (Hardware Abstraction Layer)

It is project designed to deepen my understanding of object-oriented programming in C++, software design skils, while checking bare-metal STM microcontrollers programming.
Project aims to develop a high-level abstraction layer that effectively decouples hardware-specific code from application logic, ensuring a modular, maintainable, and portable codebase.

## Project Objectives:

**1. Mastering Object-Oriented C++:** 
This project leverages advanced C++ techniques, including encapsulation, inheritance, and polymorphism, to create robust and reusable hardware abstraction modules.

**2. Bare-Metal Programming Expertise:** 
By working directly with STM microcontrollers without relying on ST's HAL, I gain knowledge of hardware operations, interrupt handling, and efficient resource management.

**3. Separation of Concerns:** 
HAL is intermediary layer that abstracts hardware details, allowing application code to remain agnostic of the underlying platform. This design facilitates easy adaptation to different hardware platforms with minimal code changes.

**4. Software Design Proficiency**:
Focus of this project is to apply and refine software design principles, aiming for a clean, efficient, and scalable architecture that adheres to best practices in software engineering.

## Current State of the Project:

At present, the repository houses both the HAL and a test application within the same codebase. This setup simplifies development and testing, ensuring that the HAL functionalities are thoroughly vetted against real-world scenarios.

### Functionalities added:
> **Note:** Not all were tested fully. I left it as its not the full point of this work.
#### Gpio:
- input
- output
- alternate function
#### Timer:
- counting timer
#### Interrupts:
- reservation for counting timer
- general purpose reservation
#### Uart:
- get and transmit using interrupts

## Future Directions:

**1. Isolate the Test Application:** 
Migrate the test application to a separate repository, enhancing the modularity of the project. This separation will streamline development processes and improve code organization.

**2. Integrate HAL as a Submodule or Library:** 
HAL should be easily integrational into the test application repository using Git submodules, fetch content or as an external library. This approach ensures independent evolution of the HAL and application code, clean and maintainable architecture.

**3. Expand HAL Capabilities:** 
Continuous development will introduce new modules and features to the HAL, covering various aspects of STM microcontroller operations such as communication protocols, power management, and peripheral control.

## Developer Instructions:

_**Cloning repo:**_

> **bash:**
>
> $ git clone https://github.com/yourusername/HAL.git
>
> $ cd HAL

### Directory Structure:

- ***lib/components*** - contains **interface and base classes** for mcu modules 
- ***lib/utils*** - contains common implementation of utilities  
- ***core/*** - contains all related to **specific mcu model ** registers, implementations of components with interfaces as from ***lib/components*** 

### Building the Project:

There is used CMake build system.

#
### oxfrd
