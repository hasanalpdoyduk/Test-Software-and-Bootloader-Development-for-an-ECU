#include "mcc_generated_files/system.h"        // MCC-generated system initialization
#include "mcc_generated_files/uart1.h"          // UART1 communication functions
#include <stdlib.h>                             // For atoi()

#define FCY 3685000UL  // i?lemcinin gerçek Fcy de?eri


// Global variables to store current PWM settings
volatile unsigned int global_duty_percent = 50;    // Default duty cycle: 50%
volatile unsigned int global_freq_hz = 310;        // Default frequency: 310 Hz

// Initializes PWM1H output on RB14
void PWM1_Init(void) {
    PTCONbits.PTEN = 0;                           // Disable PWM module
    PTCON2bits.PCLKDIV = 0;                       // PWM time base clock prescaler: 1:1

    // Calculate initial period based on frequency
    PTPER = (FCY / global_freq_hz) - 1;
    PDC1 = ((PTPER + 1UL) * global_duty_percent) / 100;   // Set initial duty cycle

    // Basic PWM configuration
    PWMCON1bits.ITB = 0;      // Not using independent time base
    PWMCON1bits.MDCS = 0;     // Not using master duty cycle
    PWMCON1bits.DTC = 0;      // No dead-time

    // Configure RB14 (PWM1H) as PWM output
    IOCON1bits.PENH = 1;
    IOCON1bits.PENL = 0;
    IOCON1bits.PMOD = 0;      // Edge-aligned mode

    PTCONbits.PTEN = 1;       // Enable PWM module
}

// Sets the PWM duty cycle (0 to 100%)
void PWM1_SetDutyPercent(unsigned int percent) {
    if (percent <= 100) {
        global_duty_percent = percent;
        PDC1 = ((PTPER + 1UL) * global_duty_percent) / 100;
    }
}

// Sets the PWM frequency in Hz
void PWM1_SetFrequency(unsigned int freq_hz) {
    if (freq_hz >= 310 && freq_hz <= 9000) { // Frequency range control
        global_freq_hz = freq_hz;
        PTPER = (FCY / global_freq_hz) - 1;
        PDC1 = ((PTPER + 1UL) * global_duty_percent) / 100;
    }
}

int main(void) {
    SYSTEM_Initialize();
    PWM1_Init();

    char uart_buffer[10];
    uint8_t index = 0;

    while (1) {
        // Bootloader trigger: 'b' karakteri gelirse reset at
        if (UART1_IsRxReady()) {
            char c = UART1_Read();

            if (c == 'b') {
                __asm__ volatile ("reset"); // Reset to bootloader
            }

            // Normal UART command buffer
            if (c >= '0' && c <= '9') {
                uart_buffer[index++] = c;
                if (index >= sizeof(uart_buffer)) index = 0;
            } else if (c == 'D') {
                uart_buffer[index] = '\0';
                PWM1_SetDutyPercent(atoi(uart_buffer));
                index = 0;
            } else if (c == 'F') {
                uart_buffer[index] = '\0';
                PWM1_SetFrequency(atoi(uart_buffer));
                index = 0;
            } else {
                index = 0; // Hatal? karakterde buffer'? s?f?rla
            }
        }
    }

    return 1;
}
