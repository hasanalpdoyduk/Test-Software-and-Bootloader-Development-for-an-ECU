
# Test Software and Bootloader Development for an ECU

A bootloader has been developed that enables firmware updates without external programmers. The system runs on a 16-bit dsPIC33 microcontroller and supports CAN and UART interfaces.

Software is securely transferred via one of these interfaces and written to the microcontroller's memory using a block-based architecture that ensures data integrity during interrupts. To streamline the update process, a Python-based graphical user interface (GUI) was created for real-time control and monitoring.

Furthermore, a custom board containing the dsPIC33 MCU was designed and manufactured, successfully testing the bootloader and a PWM control implementation.
## Hardware Components

To initially load the bootloader onto the microcontroller or test the PWM control code, an external debugger is required. In this project, Microchip’s **PICkit 5** is used to program the dsPIC33 device.

| Type         | Component                                                        |
| ----------------- | ------------------------------------------------------------------ |
| Microcontroller | [dsPIC33](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/dsPIC33EVXXXGM00X-10X-Family-Data-Sheet-DS70005144H.pdf) |
| CAN Transceiver | [MCP2561](https://ww1.microchip.com/downloads/en/DeviceDoc/20005167C.pdf) |
| LDO              | [LF50](https://www.st.com/resource/en/datasheet/lfxx.pdf) |
| TVS Diode| [SMAJ36CA](https://www.vishay.com/docs/88390/smaj50a.pdf) |
| Schottky Diode| [SS8PH10HM3](https://www.vishay.com/docs/88989/ss8ph10.pdf) |

In addition to main components, other hardware parts such as resistors, capacitors, connectors, and oscillators are listed in the [Bill of Materials (BOM)](https://github.com/hasanalpdoyduk/Test-Software-and-Bootloader-Development-for-an-ECU/blob/main/KiCAD/ECU_SW_Control/Production_Files/BOM/ECU_SW_Control.csv).


## Block Diagram

![Block Diagram](https://github.com/hasanalpdoyduk/Test-Software-and-Bootloader-Development-for-an-ECU/blob/main/Images/block_diagram_last.png)

The fully assembled PCB is shown here: [3D View of PCB](https://github.com/hasanalpdoyduk/Test-Software-and-Bootloader-Development-for-an-ECU/blob/main/Images/3D_view.pdf)


## Tools & Libraries

- KiCad: Used for schematic and PCB design.

- MATLAB Simulink Device Blocks for Microchip: Used to model and generate initial versions of embedded code.

- MPLAB X IDE: Used to compile and flash generated C code to the dsPIC33 MCU.

- Python (PyQt): Used for GUI development to support user interaction and test control.






## Supporting Sources

All technical details and explanations related to the project are available in the [project report](https://github.com/hasanalpdoyduk/Test-Software-and-Bootloader-Development-for-an-ECU/blob/main/Report_Presentation/EE402_Final_Report_AlpDoyduk_S025015_I%CC%87smailAkbas_S024094.pdf). For more in-depth insights or specific inquiries, feel free to reach out via GitHub or refer to the resources listed below.

- [MCC dsPIC33 Bootlader - Video Guide](https://www.youtube.com/watch?v=2LhW11LbNhY): A step-by-step YouTube tutorial demonstrating how to implement a bootloader for dsPIC33 using Microchip Code Configurator (MCC).

- [Microchip Bootloader Library for 16-bit Devices](https://www.microchip.com/en-us/software-library/dspic33-pic24-bootloader): Official documentation and downloadable libraries for implementing bootloaders on 16-bit dsPIC33/PIC24 microcontrollers.

- [16-bit Bootloader Using MCC - Online Course](https://mu.microchip.com/16-bit-bootloaders-using-mcc-device-side): A Microchip University course explaining how to develop a bootloader for dsPIC33 using MCC, covering both theory and practice.
## Authors

- [Hasan Alp Doyduk](https://www.github.com/hasanalpdoyduk)
- [Ismail Akbaş](https://www.github.com/ismailakbas)

Supervised by: Asst. Prof. Umut Başaran

