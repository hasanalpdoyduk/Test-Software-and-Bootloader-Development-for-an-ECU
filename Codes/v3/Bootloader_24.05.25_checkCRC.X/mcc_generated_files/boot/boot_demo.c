#include <stdbool.h>
#include <stdint.h>
#include "boot_config.h"
#include "boot_application_header.h"
#include "boot_image.h"
#include "boot_process.h"
#include "../uart1.h"

#define EXECUTION_IMAGE     0u

static bool inBootloadMode = false;
static bool executionImageRequiresValidation = true;
static bool executionImageValid = false;

static bool EnterBootloadMode(void);

void BOOT_DEMO_Initialize(void)
{
    // Gerekirse burada pre-init ekleyebilirsin, ?imdilik bo?
}

void BOOT_DEMO_Tasks(void)
{
    if (inBootloadMode == false)
    {
        if (EnterBootloadMode() == true)
        {
            inBootloadMode = true;
        }
        else
        {
            if (executionImageRequiresValidation == true)
            {
                executionImageValid = BOOT_ImageVerify(EXECUTION_IMAGE);
            }

            if (executionImageValid == false)
            {
                inBootloadMode = true;
            }

            if (inBootloadMode == false)
            {
                BOOT_StartApplication();  // Uygulama ba?lat?l?r
            }
        }
    }

    (void) BOOT_ProcessCommand(); // Bootloader ana task (UART üzerinden .hex al?r vs.)
}

static bool EnterBootloadMode(void)
{
    uint32_t timeout = 40000;  // Yakla??k birkaç milisaniyelik zaman tan?
    while (timeout--)
    {
        if (UART1_IsRxReady())
        {
            char c = UART1_Read();
            if (c == 'b')
            {
                return true;  // Bootloader moduna gir
            }
            else
            {
                return false; // Herhangi ba?ka bir karakterde atla
            }
        }
    }

    return false; // Timeout olduysa uygulamaya geç
}