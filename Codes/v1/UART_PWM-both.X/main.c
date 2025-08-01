#include "mcc_generated_files/system.h"        // MCC-generated system initialization
#include "mcc_generated_files/uart1.h"          // UART1 communication functions
#include <stdlib.h>                             // For atoi()

// Global variables to store current PWM settings
volatile unsigned int global_duty_percent = 50;    // Default duty cycle: 50%
volatile unsigned int global_freq_hz = 100;        // Default frequency: 100 Hz

// Initializes PWM1H output on RB14
void PWM1_Init(void) {
    PTCONbits.PTEN = 0;                           // Disable PWM module
    PTCON2bits.PCLKDIV = 0;                       // PWM time base clock prescaler: 1:1

    // Calculate initial period based on frequency (Fcy = 20 MHz)
    PTPER = (20000000UL / global_freq_hz) - 1;
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

        // Send feedback via UART
        UART1_Write('\n');
        UART1_Write('D'); UART1_Write('U'); UART1_Write('T'); UART1_Write('Y');
        UART1_Write('\n');
    }
}

// Sets the PWM frequency (100 to 20000 Hz)
void PWM1_SetFrequency(unsigned int freq_hz) {
    if (freq_hz >= 310 && freq_hz <= 9000) {
        unsigned long newPTPER = (20000000UL / freq_hz) - 1;

        if (newPTPER <= 65535UL) {
            PTCONbits.PTEN = 0;                            // Temporarily disable PWM
            PTPER = (unsigned int)newPTPER;
            global_freq_hz = freq_hz;

            // Recalculate duty cycle based on new period
            PDC1 = ((PTPER + 1UL) * global_duty_percent) / 100;
            PTCONbits.PTEN = 1;                            // Re-enable PWM

            // Send feedback via UART
            UART1_Write('\n');
            UART1_Write('F'); UART1_Write('R'); UART1_Write('E'); UART1_Write('Q');
            UART1_Write('\n');
        }
    }
}

// Reads 8 characters over UART: 4 digits for duty, 4 digits for frequency
void handle_uart_command(void) {
    char buffer[9] = {0};            // 8 characters + null terminator
    int i = 0;

    while (i < 8) {                  // Read until all 8 characters are received
        if (UART1_IsRxReady()) {
            char c = UART1_Read();  // Read one character from UART
            UART1_Write(c);         // Echo it back
            buffer[i++] = c;
        }
    }

    // Split the 8-character string into two 4-character parts
    char duty_str[5] = {0};
    char freq_str[5] = {0};
    for (int j = 0; j < 4; j++) {
        duty_str[j] = buffer[j];
        freq_str[j] = buffer[j + 4];
    }

    // Convert string to integer
    unsigned int new_duty = atoi(duty_str);
    unsigned int new_freq = atoi(freq_str);

    // Apply new settings
    PWM1_SetDutyPercent(new_duty);
    PWM1_SetFrequency(new_freq);
}

// Main function
int main(void) {
    SYSTEM_Initialize();        // Initialize clock, UART, etc.
    PWM1_Init();                // Start PWM module

    // Send initial "READY" message
    UART1_Write('\n');
    UART1_Write('R'); UART1_Write('E'); UART1_Write('A'); UART1_Write('D'); UART1_Write('Y');
    UART1_Write('\n');

    // Infinite loop to handle UART commands
    while (1) {
        handle_uart_command();
    }

    return 1;
}
