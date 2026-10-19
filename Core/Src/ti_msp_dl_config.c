/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerG_backupConfig gPWM_R1Backup;
DL_TimerG_backupConfig gPWM_L2Backup;
DL_TimerA_backupConfig gPWM_R2Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_L1_init();
    SYSCFG_DL_PWM_R1_init();
    SYSCFG_DL_PWM_L2_init();
    SYSCFG_DL_PWM_R2_init();
    SYSCFG_DL_MYUART_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWM_R1Backup.backupRdy 	= false;
	gPWM_L2Backup.backupRdy 	= false;
	gPWM_R2Backup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_saveConfiguration(PWM_R1_INST, &gPWM_R1Backup);
	retStatus &= DL_TimerG_saveConfiguration(PWM_L2_INST, &gPWM_L2Backup);
	retStatus &= DL_TimerA_saveConfiguration(PWM_R2_INST, &gPWM_R2Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerG_restoreConfiguration(PWM_R1_INST, &gPWM_R1Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(PWM_L2_INST, &gPWM_L2Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(PWM_R2_INST, &gPWM_R2Backup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_L1_INST);
    DL_TimerG_reset(PWM_R1_INST);
    DL_TimerG_reset(PWM_L2_INST);
    DL_TimerA_reset(PWM_R2_INST);
    DL_UART_Main_reset(MYUART_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_L1_INST);
    DL_TimerG_enablePower(PWM_R1_INST);
    DL_TimerG_enablePower(PWM_L2_INST);
    DL_TimerA_enablePower(PWM_R2_INST);
    DL_UART_Main_enablePower(MYUART_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_L1_C0_IOMUX,GPIO_PWM_L1_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_L1_C0_PORT, GPIO_PWM_L1_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_L1_C1_IOMUX,GPIO_PWM_L1_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_L1_C1_PORT, GPIO_PWM_L1_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_R1_C0_IOMUX,GPIO_PWM_R1_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_R1_C0_PORT, GPIO_PWM_R1_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_R1_C1_IOMUX,GPIO_PWM_R1_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_R1_C1_PORT, GPIO_PWM_R1_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_L2_C0_IOMUX,GPIO_PWM_L2_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_L2_C0_PORT, GPIO_PWM_L2_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_L2_C1_IOMUX,GPIO_PWM_L2_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_L2_C1_PORT, GPIO_PWM_L2_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_R2_C0_IOMUX,GPIO_PWM_R2_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_R2_C0_PORT, GPIO_PWM_R2_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_R2_C1_IOMUX,GPIO_PWM_R2_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_R2_C1_PORT, GPIO_PWM_R2_C1_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_MYUART_IOMUX_TX, GPIO_MYUART_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_MYUART_IOMUX_RX, GPIO_MYUART_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalInput(L1_Enconder_A_pin_14_IOMUX);

    DL_GPIO_initDigitalInput(L1_Enconder_B_pin_15_IOMUX);

    DL_GPIO_initDigitalInput(L2_Enconder_A_pin_24_IOMUX);

    DL_GPIO_initDigitalInput(L2_Enconder_B_pin_25_IOMUX);

    DL_GPIO_initDigitalInput(R1_Enconder_A_pin_8_IOMUX);

    DL_GPIO_initDigitalInput(R1_Enconder_B_pin_9_IOMUX);

    DL_GPIO_initDigitalInput(R2_Enconder_A_pin_21_IOMUX);

    DL_GPIO_initDigitalInput(R2_Enconder_B_pin_22_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X1_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X2_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X3_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X4_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X5_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X6_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X7_IOMUX);

    DL_GPIO_initDigitalInput(IR_X_X8_IOMUX);

    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_14_EDGE_RISE |
		DL_GPIO_PIN_15_EDGE_RISE |
		DL_GPIO_PIN_8_EDGE_RISE |
		DL_GPIO_PIN_9_EDGE_RISE);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_24_EDGE_RISE |
		DL_GPIO_PIN_25_EDGE_RISE |
		DL_GPIO_PIN_21_EDGE_RISE |
		DL_GPIO_PIN_22_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, L1_Enconder_A_pin_14_PIN |
		L1_Enconder_B_pin_15_PIN |
		L2_Enconder_A_pin_24_PIN |
		L2_Enconder_B_pin_25_PIN |
		R1_Enconder_A_pin_8_PIN |
		R1_Enconder_B_pin_9_PIN |
		R2_Enconder_A_pin_21_PIN |
		R2_Enconder_B_pin_22_PIN);
    DL_GPIO_enableInterrupt(GPIOA, L1_Enconder_A_pin_14_PIN |
		L1_Enconder_B_pin_15_PIN |
		L2_Enconder_A_pin_24_PIN |
		L2_Enconder_B_pin_25_PIN |
		R1_Enconder_A_pin_8_PIN |
		R1_Enconder_B_pin_9_PIN |
		R2_Enconder_A_pin_21_PIN |
		R2_Enconder_B_pin_22_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_enableMFCLK();

}


/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   100000 Hz = 4000000 Hz / (8 * (39 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_L1ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 39U
};

static const DL_TimerG_PWMConfig gPWM_L1Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_L1_init(void) {

    DL_TimerG_setClockConfig(
        PWM_L1_INST, (DL_TimerG_ClockConfig *) &gPWM_L1ClockConfig);

    DL_TimerG_initPWMMode(
        PWM_L1_INST, (DL_TimerG_PWMConfig *) &gPWM_L1Config);

    DL_TimerG_setCaptureCompareValue(PWM_L1_INST, 1000, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_L1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_L1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptureCompareValue(PWM_L1_INST, 1000, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_L1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_L1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_enableClock(PWM_L1_INST);


    
    DL_TimerG_setCCPDirection(PWM_L1_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}
/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   100000 Hz = 4000000 Hz / (8 * (39 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_R1ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 39U
};

static const DL_TimerG_PWMConfig gPWM_R1Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_R1_init(void) {

    DL_TimerG_setClockConfig(
        PWM_R1_INST, (DL_TimerG_ClockConfig *) &gPWM_R1ClockConfig);

    DL_TimerG_initPWMMode(
        PWM_R1_INST, (DL_TimerG_PWMConfig *) &gPWM_R1Config);

    DL_TimerG_setCaptureCompareValue(PWM_R1_INST, 1000, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_R1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_R1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptureCompareValue(PWM_R1_INST, 1000, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_R1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_R1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_enableClock(PWM_R1_INST);


    
    DL_TimerG_setCCPDirection(PWM_R1_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}
/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   100000 Hz = 4000000 Hz / (8 * (39 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_L2ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 39U
};

static const DL_TimerG_PWMConfig gPWM_L2Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_L2_init(void) {

    DL_TimerG_setClockConfig(
        PWM_L2_INST, (DL_TimerG_ClockConfig *) &gPWM_L2ClockConfig);

    DL_TimerG_initPWMMode(
        PWM_L2_INST, (DL_TimerG_PWMConfig *) &gPWM_L2Config);

    DL_TimerG_setCaptureCompareValue(PWM_L2_INST, 1000, DL_TIMER_CC_0_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_L2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_L2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptureCompareValue(PWM_L2_INST, 1000, DL_TIMER_CC_1_INDEX);
    DL_TimerG_setCaptureCompareOutCtl(PWM_L2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_L2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_enableClock(PWM_L2_INST);


    
    DL_TimerG_setCCPDirection(PWM_L2_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}
/*
 * Timer clock configuration to be sourced by  / 8 (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   100000 Hz = 4000000 Hz / (8 * (39 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_R2ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 39U
};

static const DL_TimerA_PWMConfig gPWM_R2Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_R2_init(void) {

    DL_TimerA_setClockConfig(
        PWM_R2_INST, (DL_TimerA_ClockConfig *) &gPWM_R2ClockConfig);

    DL_TimerA_initPWMMode(
        PWM_R2_INST, (DL_TimerA_PWMConfig *) &gPWM_R2Config);

    DL_TimerA_setCaptureCompareValue(PWM_R2_INST, 1000, DL_TIMER_CC_0_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(PWM_R2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_R2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptureCompareValue(PWM_R2_INST, 1000, DL_TIMER_CC_1_INDEX);
    DL_TimerA_setCaptureCompareOutCtl(PWM_R2_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_R2_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_enableClock(PWM_R2_INST);


    
    DL_TimerA_setCCPDirection(PWM_R2_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );

}



static const DL_UART_Main_ClockConfig gMYUARTClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gMYUARTConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_MYUART_init(void)
{
    DL_UART_Main_setClockConfig(MYUART_INST, (DL_UART_Main_ClockConfig *) &gMYUARTClockConfig);

    DL_UART_Main_init(MYUART_INST, (DL_UART_Main_Config *) &gMYUARTConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(MYUART_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(MYUART_INST, MYUART_IBRD_32_MHZ_115200_BAUD, MYUART_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(MYUART_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(MYUART_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /*
     * Initializes the SysTick period to 1.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    DL_SYSTICK_config(32000);
}

