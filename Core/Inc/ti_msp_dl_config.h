/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_L1 */
#define PWM_L1_INST                                                        TIMG0
#define PWM_L1_INST_IRQHandler                                  TIMG0_IRQHandler
#define PWM_L1_INST_INT_IRQN                                    (TIMG0_INT_IRQn)
#define PWM_L1_INST_CLK_FREQ                                              100000
/* GPIO defines for channel 0 */
#define GPIO_PWM_L1_C0_PORT                                                GPIOA
#define GPIO_PWM_L1_C0_PIN                                        DL_GPIO_PIN_12
#define GPIO_PWM_L1_C0_IOMUX                                     (IOMUX_PINCM34)
#define GPIO_PWM_L1_C0_IOMUX_FUNC                    IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_L1_C0_IDX                                   DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_L1_C1_PORT                                                GPIOA
#define GPIO_PWM_L1_C1_PIN                                        DL_GPIO_PIN_13
#define GPIO_PWM_L1_C1_IOMUX                                     (IOMUX_PINCM35)
#define GPIO_PWM_L1_C1_IOMUX_FUNC                    IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_L1_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_R1 */
#define PWM_R1_INST                                                        TIMG6
#define PWM_R1_INST_IRQHandler                                  TIMG6_IRQHandler
#define PWM_R1_INST_INT_IRQN                                    (TIMG6_INT_IRQn)
#define PWM_R1_INST_CLK_FREQ                                              100000
/* GPIO defines for channel 0 */
#define GPIO_PWM_R1_C0_PORT                                                GPIOB
#define GPIO_PWM_R1_C0_PIN                                         DL_GPIO_PIN_6
#define GPIO_PWM_R1_C0_IOMUX                                     (IOMUX_PINCM23)
#define GPIO_PWM_R1_C0_IOMUX_FUNC                    IOMUX_PINCM23_PF_TIMG6_CCP0
#define GPIO_PWM_R1_C0_IDX                                   DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_R1_C1_PORT                                                GPIOB
#define GPIO_PWM_R1_C1_PIN                                         DL_GPIO_PIN_7
#define GPIO_PWM_R1_C1_IOMUX                                     (IOMUX_PINCM24)
#define GPIO_PWM_R1_C1_IOMUX_FUNC                    IOMUX_PINCM24_PF_TIMG6_CCP1
#define GPIO_PWM_R1_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_L2 */
#define PWM_L2_INST                                                        TIMG7
#define PWM_L2_INST_IRQHandler                                  TIMG7_IRQHandler
#define PWM_L2_INST_INT_IRQN                                    (TIMG7_INT_IRQn)
#define PWM_L2_INST_CLK_FREQ                                              100000
/* GPIO defines for channel 0 */
#define GPIO_PWM_L2_C0_PORT                                                GPIOA
#define GPIO_PWM_L2_C0_PIN                                        DL_GPIO_PIN_26
#define GPIO_PWM_L2_C0_IOMUX                                     (IOMUX_PINCM59)
#define GPIO_PWM_L2_C0_IOMUX_FUNC                    IOMUX_PINCM59_PF_TIMG7_CCP0
#define GPIO_PWM_L2_C0_IDX                                   DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_L2_C1_PORT                                                GPIOA
#define GPIO_PWM_L2_C1_PIN                                        DL_GPIO_PIN_27
#define GPIO_PWM_L2_C1_IOMUX                                     (IOMUX_PINCM60)
#define GPIO_PWM_L2_C1_IOMUX_FUNC                    IOMUX_PINCM60_PF_TIMG7_CCP1
#define GPIO_PWM_L2_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_R2 */
#define PWM_R2_INST                                                        TIMA0
#define PWM_R2_INST_IRQHandler                                  TIMA0_IRQHandler
#define PWM_R2_INST_INT_IRQN                                    (TIMA0_INT_IRQn)
#define PWM_R2_INST_CLK_FREQ                                              100000
/* GPIO defines for channel 0 */
#define GPIO_PWM_R2_C0_PORT                                                GPIOB
#define GPIO_PWM_R2_C0_PIN                                         DL_GPIO_PIN_8
#define GPIO_PWM_R2_C0_IOMUX                                     (IOMUX_PINCM25)
#define GPIO_PWM_R2_C0_IOMUX_FUNC                    IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_PWM_R2_C0_IDX                                   DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_R2_C1_PORT                                                GPIOB
#define GPIO_PWM_R2_C1_PIN                                         DL_GPIO_PIN_9
#define GPIO_PWM_R2_C1_IOMUX                                     (IOMUX_PINCM26)
#define GPIO_PWM_R2_C1_IOMUX_FUNC                    IOMUX_PINCM26_PF_TIMA0_CCP1
#define GPIO_PWM_R2_C1_IDX                                   DL_TIMER_CC_1_INDEX



/* Defines for MYUART */
#define MYUART_INST                                                        UART0
#define MYUART_INST_IRQHandler                                  UART0_IRQHandler
#define MYUART_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_MYUART_RX_PORT                                                GPIOA
#define GPIO_MYUART_TX_PORT                                                GPIOA
#define GPIO_MYUART_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_MYUART_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_MYUART_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_MYUART_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_MYUART_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_MYUART_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define MYUART_BAUD_RATE                                                (115200)
#define MYUART_IBRD_32_MHZ_115200_BAUD                                      (17)
#define MYUART_FBRD_32_MHZ_115200_BAUD                                      (23)





/* Port definition for Pin Group L1_Enconder_A */
#define L1_Enconder_A_PORT                                               (GPIOA)

/* Defines for pin_14: GPIOA.14 with pinCMx 36 on package pin 7 */
// groups represented: ["L1_Enconder_B","L2_Enconder_A","L2_Enconder_B","R1_Enconder_A","R1_Enconder_B","R2_Enconder_A","R2_Enconder_B","L1_Enconder_A"]
// pins affected: ["pin_15","pin_24","pin_25","pin_8","pin_9","pin_21","pin_22","pin_14"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define L1_Enconder_A_pin_14_IIDX                           (DL_GPIO_IIDX_DIO14)
#define L1_Enconder_A_pin_14_PIN                                (DL_GPIO_PIN_14)
#define L1_Enconder_A_pin_14_IOMUX                               (IOMUX_PINCM36)
/* Port definition for Pin Group L1_Enconder_B */
#define L1_Enconder_B_PORT                                               (GPIOA)

/* Defines for pin_15: GPIOA.15 with pinCMx 37 on package pin 8 */
#define L1_Enconder_B_pin_15_IIDX                           (DL_GPIO_IIDX_DIO15)
#define L1_Enconder_B_pin_15_PIN                                (DL_GPIO_PIN_15)
#define L1_Enconder_B_pin_15_IOMUX                               (IOMUX_PINCM37)
/* Port definition for Pin Group L2_Enconder_A */
#define L2_Enconder_A_PORT                                               (GPIOA)

/* Defines for pin_24: GPIOA.24 with pinCMx 54 on package pin 25 */
#define L2_Enconder_A_pin_24_IIDX                           (DL_GPIO_IIDX_DIO24)
#define L2_Enconder_A_pin_24_PIN                                (DL_GPIO_PIN_24)
#define L2_Enconder_A_pin_24_IOMUX                               (IOMUX_PINCM54)
/* Port definition for Pin Group L2_Enconder_B */
#define L2_Enconder_B_PORT                                               (GPIOA)

/* Defines for pin_25: GPIOA.25 with pinCMx 55 on package pin 26 */
#define L2_Enconder_B_pin_25_IIDX                           (DL_GPIO_IIDX_DIO25)
#define L2_Enconder_B_pin_25_PIN                                (DL_GPIO_PIN_25)
#define L2_Enconder_B_pin_25_IOMUX                               (IOMUX_PINCM55)
/* Port definition for Pin Group R1_Enconder_A */
#define R1_Enconder_A_PORT                                               (GPIOA)

/* Defines for pin_8: GPIOA.8 with pinCMx 19 on package pin 54 */
#define R1_Enconder_A_pin_8_IIDX                             (DL_GPIO_IIDX_DIO8)
#define R1_Enconder_A_pin_8_PIN                                  (DL_GPIO_PIN_8)
#define R1_Enconder_A_pin_8_IOMUX                                (IOMUX_PINCM19)
/* Port definition for Pin Group R1_Enconder_B */
#define R1_Enconder_B_PORT                                               (GPIOA)

/* Defines for pin_9: GPIOA.9 with pinCMx 20 on package pin 55 */
#define R1_Enconder_B_pin_9_IIDX                             (DL_GPIO_IIDX_DIO9)
#define R1_Enconder_B_pin_9_PIN                                  (DL_GPIO_PIN_9)
#define R1_Enconder_B_pin_9_IOMUX                                (IOMUX_PINCM20)
/* Port definition for Pin Group R2_Enconder_A */
#define R2_Enconder_A_PORT                                               (GPIOA)

/* Defines for pin_21: GPIOA.21 with pinCMx 46 on package pin 17 */
#define R2_Enconder_A_pin_21_IIDX                           (DL_GPIO_IIDX_DIO21)
#define R2_Enconder_A_pin_21_PIN                                (DL_GPIO_PIN_21)
#define R2_Enconder_A_pin_21_IOMUX                               (IOMUX_PINCM46)
/* Port definition for Pin Group R2_Enconder_B */
#define R2_Enconder_B_PORT                                               (GPIOA)

/* Defines for pin_22: GPIOA.22 with pinCMx 47 on package pin 18 */
#define R2_Enconder_B_pin_22_IIDX                           (DL_GPIO_IIDX_DIO22)
#define R2_Enconder_B_pin_22_PIN                                (DL_GPIO_PIN_22)
#define R2_Enconder_B_pin_22_IOMUX                               (IOMUX_PINCM47)
/* Defines for X1: GPIOA.28 with pinCMx 3 on package pin 35 */
#define IR_X_X1_PORT                                                     (GPIOA)
#define IR_X_X1_PIN                                             (DL_GPIO_PIN_28)
#define IR_X_X1_IOMUX                                             (IOMUX_PINCM3)
/* Defines for X2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define IR_X_X2_PORT                                                     (GPIOA)
#define IR_X_X2_PIN                                             (DL_GPIO_PIN_31)
#define IR_X_X2_IOMUX                                             (IOMUX_PINCM6)
/* Defines for X3: GPIOA.2 with pinCMx 7 on package pin 42 */
#define IR_X_X3_PORT                                                     (GPIOA)
#define IR_X_X3_PIN                                              (DL_GPIO_PIN_2)
#define IR_X_X3_IOMUX                                             (IOMUX_PINCM7)
/* Defines for X4: GPIOB.24 with pinCMx 52 on package pin 23 */
#define IR_X_X4_PORT                                                     (GPIOB)
#define IR_X_X4_PIN                                             (DL_GPIO_PIN_24)
#define IR_X_X4_IOMUX                                            (IOMUX_PINCM52)
/* Defines for X5: GPIOB.20 with pinCMx 48 on package pin 19 */
#define IR_X_X5_PORT                                                     (GPIOB)
#define IR_X_X5_PIN                                             (DL_GPIO_PIN_20)
#define IR_X_X5_IOMUX                                            (IOMUX_PINCM48)
/* Defines for X6: GPIOB.19 with pinCMx 45 on package pin 16 */
#define IR_X_X6_PORT                                                     (GPIOB)
#define IR_X_X6_PIN                                             (DL_GPIO_PIN_19)
#define IR_X_X6_IOMUX                                            (IOMUX_PINCM45)
/* Defines for X7: GPIOB.18 with pinCMx 44 on package pin 15 */
#define IR_X_X7_PORT                                                     (GPIOB)
#define IR_X_X7_PIN                                             (DL_GPIO_PIN_18)
#define IR_X_X7_IOMUX                                            (IOMUX_PINCM44)
/* Defines for X8: GPIOA.7 with pinCMx 14 on package pin 49 */
#define IR_X_X8_PORT                                                     (GPIOA)
#define IR_X_X8_PIN                                              (DL_GPIO_PIN_7)
#define IR_X_X8_IOMUX                                            (IOMUX_PINCM14)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_L1_init(void);
void SYSCFG_DL_PWM_R1_init(void);
void SYSCFG_DL_PWM_L2_init(void);
void SYSCFG_DL_PWM_R2_init(void);
void SYSCFG_DL_MYUART_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
