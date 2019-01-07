# CDH Firmware CSDC5

## Overview
This repository contains firmware for the UBC Orbit Command and Data Handling system. The goal of CDH is to provide automatic on-board satellite operation, along with command-driven operation when requested by ground. In the process, CDH collects telemetry for health assessment of the satellite and handles any detected on-orbit errors. CDH must be a reliable, self-sustaining system to enable the payload to focus on mission execution, and enable other sub-systems to support the payload. The payload that this CDH system has been designed to support is:

* On-demand photo of specified location and downlink of photo to amateur radio operators worldwide

## Trillium
*Information to come.*

## Software Components
* **FreeRTOS V9:** real-time OS commonly used in embedded systems. Helps with prioritizing different functions and suspending tasks where no longer needed.
* **Command System:** *Structure TBD*
* **Filesystem:** *TBD*

## Hardware Components
* **STMicroelectronics STM32H743ZIT:** main microcontroller for the CDH. Chosen for its memory capacity, peripheral count, ECC flash, and embedded hardware features.
* **MRAM:** non-volatile memory storage for CDH, used for telemetry and command storage. MRAM performs well under radiation, and is available in a large enough capacity to meet our requirements.
* **(Embedded) Real-Time Clock:** embedded in MCU, used to timestamp satellite telemetry and provide a time reference for commands.
* **(Embedded) Temperature Sensor:** embedded in MCU, monitors CDH board temperature to ensure it is within operating limits.
* **eFuse:** monitors current draw of all components on the CDH board, and cuts power when this current draw spikes to unreasonable values to mitigate single even latchups (SEL). Also monitors for overvoltage and undervoltage.

## Documentation
### Technical Documentation
* [CDH Design Document](https://docs.google.com/document/d/1zeB4NwtlgtX1g_muLqJlgJFMrVG3V4IbW7q0S0x1hv8/edit): document outlining the high-level design of the CDH system and motivations for it
* [CDH Requirements Document](https://docs.google.com/document/d/1n8n077lcpQeHJViyi5_1BgQtS7tgomw-C6Bp_QjgJ1I/edit#): detailed list of design requirements for all features of the CDH system

### Educational Resources
* [FreeRTOS Intro Powerpoint](https://drive.google.com/open?id=1kQj6Hq9gyHxC9R7xSqlmpMgZxKrHSkgS)
* *More to come soon!*

### STM32H743ZI Resources
* [Technical Reference Manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/group0/c9/a3/76/fa/55/46/45/fa/DM00314099/files/DM00314099.pdf/jcr:content/translations/en.DM00314099.pdf): detailed documentation on all peripherals and their possible configurations
* [Datasheet](https://www.st.com/resource/en/datasheet/stm32h743bi.pdf): useful electrical and pinout documentation
* [Nucleo 144 Board Manual](https://www.st.com/content/ccc/resource/technical/document/user_manual/group0/26/49/90/2e/33/0d/4a/da/DM00244518/files/DM00244518.pdf/jcr:content/translations/en.DM00244518.pdf): pin configurations for the Nucleo 144 Board and instructions for developing with it 

### STM32F401RE Resources
* [Technical Reference Manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/5d/b1/ef/b2/a1/66/40/80/DM00096844.pdf/files/DM00096844.pdf/jcr:content/translations/en.DM00096844.pdf): detailed documentation on all peripherals and their possible configurations
* [Datasheet](https://www.st.com/resource/en/datasheet/stm32f401re.pdf): useful electrical and pinout documentation
* [Nucleo 64 Board Manual](https://www.st.com/content/ccc/resource/technical/document/user_manual/98/2e/fa/4b/e0/82/43/b7/DM00105823.pdf/files/DM00105823.pdf/jcr:content/translations/en.DM00105823.pdf): pin configurations for the Nucleo 64 Board and instructions for developing with it 

### FreeRTOS Resources
* [FreeRTOS V10 Reference Manual](http://www.freertos.org/Documentation/FreeRTOS_Reference_Manual_V10.0.0.pdf)
* [FreeRTOS Tutorial Guide](https://www.freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf)
* [FreeRTOS Support Forum](http://www.freertos.org/FreeRTOS_Support_Forum_Archive/freertos_support_forum_archive_index.html)

