
# Test Software and Bootloader Development for an ECU

A bootloader has been developed that enables firmware updates without external programmers. The system runs on a 16-bit dsPIC33 microcontroller and supports CAN and UART interfaces.

Software is securely transferred via one of these interfaces and written to the microcontroller's memory using a block-based architecture that ensures data integrity during interrupts. To streamline the update process, a Python-based graphical user interface (GUI) was created for real-time control and monitoring.

Furthermore, a custom board containing the dsPIC33 MCU was designed and manufactured, successfully testing the bootloader and a PWM control implementation.
## Hardware Components

| Usage         | Component                                                        |
| ----------------- | ------------------------------------------------------------------ |
| Microcontroller | [dsPIC33](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/dsPIC33EVXXXGM00X-10X-Family-Data-Sheet-DS70005144H.pdf) |
| CAN Transceiver | [MCP2561](https://ww1.microchip.com/downloads/en/DeviceDoc/20005167C.pdf) |
| LDO              | [LF50](https://www.st.com/resource/en/datasheet/lfxx.pdf) |
| TVS Diode| [SMAJ36CA](https://www.vishay.com/docs/88390/smaj50a.pdf) |
| Schottky Diode| [SS8PH10HM3](https://www.vishay.com/docs/88989/ss8ph10.pdf) |

To initially load the bootloader onto the microcontroller, an external debugger is required. In this project, Microchip’s **PICkit 5** is used to program the dsPIC33 device.

## Block Diagram

![Block Diagram](https://github.com/hasanalpdoyduk/Test-Software-and-Bootloader-Development-for-an-ECU/blob/main/Images/block_diagram_last.png)


## Software Components

| Usage         | Component                                                        |
| ----------------- | ------------------------------------------------------------------ |
| Microcontroller | [dsPIC33](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/dsPIC33EVXXXGM00X-10X-Family-Data-Sheet-DS70005144H.pdf) |
| CAN Transceiver | [MCP2561](https://ww1.microchip.com/downloads/en/DeviceDoc/20005167C.pdf) |
| LDO              | [LF50](https://www.st.com/resource/en/datasheet/lfxx.pdf) |
| TVS Diode| [SMAJ36CA](https://www.vishay.com/docs/88390/smaj50a.pdf) |
| Schottky Diode| [SS8PH10HM3](https://www.vishay.com/docs/88989/ss8ph10.pdf) |



## Authors

- [Hasan Alp Doyduk](https://www.github.com/hasanalpdoyduk)
- [Ismail Akbaş](https://www.github.com/ismailakbas)
Supervised by: Asst. Prof. Umut Başaran

