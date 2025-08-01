/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * -------------------------------------------------------------------
 * MPLAB Device Blocks for Simulink v3.58 (26-Nov-2024)
 *
 *   Product Page:  https://www.mathworks.com/matlabcentral/fileexchange/71892
 *           Forum: https://forum.microchip.com/s/sub-forums?&subForumId=a553l000000J2rNAAS&forumId=a553l000000J2pvAAC&subForumName=MATLAB
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: digital_output_2_0_main.c
 *
 * Code generated for Simulink model 'digital_output_2_0'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Jan  3 12:54:11 2025
 */

/* Set Fuses Options */

#pragma config FNOSC = FRC
#pragma config OSCIOFNC = ON, PLLKEN = ON
#pragma config FWDTEN = OFF
#pragma config PWMLOCK = OFF
#pragma config DMTEN = DISABLE

#define MCHP_isMainFile
#include "digital_output_2_0.h"
#include "digital_output_2_0_private.h"

/* Microchip Global Variables */
/* Solver mode : MultiTasking */
int main()
{
  /* Initialize model */

  /* Configure Pins as Analog or Digital */
  /* Configure Remappables Pins */

  /* Configure Digitals I/O directions */
  TRISB = 0xFFEF;                      /* Port input (1) / output (0) */

  /* Initialize model */
  digital_output_2_0_initialize();

  /* Configure Timers */
  /* --- TIMER 1 --- This timer is enabled at end of configuration functions. */
  T1CON = 0;                           /* Stop Timer 1 and resets control register */
  _T1IP = 2;                           /* Set timer Interrupt Priority */
  _T1IF = 0;                           /* Reset pending Interrupt */
  _T1IE = 1;                           /* Enable Timer Interrupt. */
  PR1 = 0x0E64;                        /* Period */

  /* Enable Time-step */
  TMR1 = 0x0E63;                       /* Initialize Timer Value */
  T1CONbits.TON = 1;                /* Start timer 1. Timer 1 is the source trigger for the model Time-step */

  /* Main Loop */
  for (;;) ;

  /* Terminate model */
  digital_output_2_0_terminate();
}                                      /* end of main() */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
