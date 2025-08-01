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
 * File: digital_output_2_0.c
 *
 * Code generated for Simulink model 'digital_output_2_0'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Fri Jan  3 12:54:11 2025
 */

#include "digital_output_2_0.h"
#include "rtwtypes.h"

/* Block signals and states (default storage) */
DW_digital_output_2_0_T digital_output_2_0_DW;

/* Real-time model */
static RT_MODEL_digital_output_2_0_T digital_output_2_0_M_;
RT_MODEL_digital_output_2_0_T *const digital_output_2_0_M = &digital_output_2_0_M_;

/* Model step function for TID0 */
void digital_output_2_0_step0(void)    /* Sample time: [0.001s, 0.0s] */
{
  /* (no output/update code required) */
}

/* Model step function for TID1 */
void digital_output_2_0_step1(void)    /* Sample time: [1.0s, 0.0s] */
{
  uint8_T rtb_Output;
  boolean_T rtb_DataTypeConversion;

  /* UnitDelay: '<S1>/Output' */
  rtb_Output = digital_output_2_0_DW.Output_DSTATE;

  /* Switch: '<S4>/FixPt Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  UnitDelay: '<S1>/Output'
   */
  digital_output_2_0_DW.Output_DSTATE = 0U;

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  rtb_DataTypeConversion = (rtb_Output != 0);

  /* S-Function (MCHP_Digital_Output_Write): '<S2>/Digital Output Write' */
  LATBbits.LATB4 = rtb_DataTypeConversion;
}

/* Model initialize function */
void digital_output_2_0_initialize(void)
{
  /* Registration code */

  /* Set task counter limit used by the static main program */
  (digital_output_2_0_M)->Timing.TaskCounters.cLimit[0] = 1;
  (digital_output_2_0_M)->Timing.TaskCounters.cLimit[1] = 1000;

  /* Start for S-Function (MCHP_Master): '<Root>/Microchip Master' */

  /* S-Function "Microchip MASTER" initialization Block: <Root>/Microchip Master */
}

/* Model terminate function */
void digital_output_2_0_terminate(void)
{
  /* (no terminate code required) */
}

/* Scheduler */
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
{
  {
    struct {
      unsigned int Flags1 : 1;
    } static volatile Overrun __attribute__ ((near)) ;

    struct {
      unsigned int Flags1 : 1;
    } static volatile event __attribute__ ((near)) ;

    struct {
      uint_T Task1;                    /* 1.0s periodic task. Max value is 1000 */
    } static taskCounter __attribute__ ((near)) = {
      .Task1 = 1                       /* Offset is 0 (1000 + 1 - 0 including pre-decrement */
    };

    _T1IF = 0;                         /* Re-enable interrupt */

    /* Check subrate overrun, set rates that need to run this time step*/
    taskCounter.Task1--;               /* Decrement task internal counter */
    if (taskCounter.Task1 == 0) {      /* task dropped on overload */
      taskCounter.Task1 = (uint16_T) 1000;/* 1.0s periodic task. Max value is 1000 */
      event.Flags1 = 1U;               /* Flag tag to be executed */
    }

    /* ---------- Handle model base rate Task 0 ---------- */
    digital_output_2_0_step0();

    /* Get model outputs here */
    if (_T1IF ) {
      return;                          /* Will re-enter into the interrupt */
    }

    /* Re-Enable Interrupt. IPL value is 2 at this point */
    _IPL0 = 1;                         /* Enable Scheduler re-entrant interrupt. Lower IPL from 2 to 1 */
    _IPL1 = 0;

    /* Step the model for any subrate */
    /* ---------- Handle Task 1 ---------- */
    if (Overrun.Flags1) {
      /* Priority to higher rate steps interrupted */
      return;
    }

    while (event.Flags1) {             /* Execute task tid 1 */
      Overrun.Flags1 = 1U;
      event.Flags1 = 0U;
      digital_output_2_0_step1();

      /* Get model outputs here */
    }

    Overrun.Flags1 = 0U;

    /* Disable Interrupt. IPL value is 1 at this point */
    _IPL1 = 1;                         /* Disable Scheduler Interrupts. Rise IPL from 1 to 2 */
    _IPL0 = 0;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
