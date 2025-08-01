#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart1.h"

int main(void)
{
    SYSTEM_Initialize();

    while (1)
    {
        // UART'tan 'b' karakteri al?n?rsa bootloader'a dönmek için reset at
        if (UART1_IsRxReady())
        {
            char c = UART1_Read();
            if (c == 'b')
            {
                __asm__ volatile ("reset");  // yaz?l?msal reset
            }
        }

        // RB4 pinini HIGH yap (örnek uygulama)
        LATBbits.LATB4 = 1;
    }

    return 1;
}
