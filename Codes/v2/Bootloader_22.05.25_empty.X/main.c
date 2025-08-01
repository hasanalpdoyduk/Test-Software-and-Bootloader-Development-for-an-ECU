#include "mcc_generated_files/system.h"
#include "mcc_generated_files/boot/boot_demo.h"
#include "mcc_generated_files/uart1.h"

int main(void)
{
    SYSTEM_Initialize();            // clock + UART init
    BOOT_DEMO_Initialize();        // de?i?medi, bo? kalabilir

    while (1)
    {
        BOOT_DEMO_Tasks();        // içinde bootloader'a girilip girilmeyece?ine karar veriliyor
    }

    return 1;
}
