#include "bsp_at8236.h"
#include "ti_msp_dl_config.h"

/*
 * SysConfig uses edge-aligned DOWN-count PWM with period 1000. A compare
 * value of 999 gives approximately 0% high time; a value of 0 gives nearly
 * 100%. The public motor API uses the opposite, intuitive duty direction.
 */
static uint16_t compare_for_duty(uint16_t duty)
{
    if (duty > MOTOR_MAX_PULSE) {
        duty = MOTOR_MAX_PULSE;
    }
    return (uint16_t)(MOTOR_MAX_PULSE - duty);
}

void init_motor(void)
{
    /* The tracking application starts L1 and R1 only. */
    Motor_Set_Pwm(Motor_M1, 0);
    Motor_Set_Pwm(Motor_M3, 0);
    DL_TimerG_startCounter(PWM_L1_INST);
    DL_TimerG_startCounter(PWM_R1_INST);
}

void L1_control(uint16_t motor_speed, uint8_t dir)
{
    const uint16_t compare = compare_for_duty(motor_speed);
    if (dir != 0U) {
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_1_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, compare, DL_TIMER_CC_0_INDEX);
    } else {
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, compare, DL_TIMER_CC_1_INDEX);
    }
}

void L2_control(uint16_t motor_speed, uint8_t dir)
{
    const uint16_t compare = compare_for_duty(motor_speed);
    if (dir != 0U) {
        DL_TimerG_setCaptureCompareValue(PWM_L2_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_1_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_L2_INST, compare, DL_TIMER_CC_0_INDEX);
    } else {
        DL_TimerG_setCaptureCompareValue(PWM_L2_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_L2_INST, compare, DL_TIMER_CC_1_INDEX);
    }
}

void R1_control(uint16_t motor_speed, uint8_t dir)
{
    const uint16_t compare = compare_for_duty(motor_speed);
    if (dir != 0U) {
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_1_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, compare, DL_TIMER_CC_0_INDEX);
    } else {
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_0_INDEX);
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, compare, DL_TIMER_CC_1_INDEX);
    }
}

void R2_control(uint16_t motor_speed, uint8_t dir)
{
    const uint16_t compare = compare_for_duty(motor_speed);
    /* R2's forward direction is opposite the other three channels. */
    if (dir != 0U) {
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_0_INDEX);
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, compare, DL_TIMER_CC_1_INDEX);
    } else {
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, MOTOR_MAX_PULSE, DL_TIMER_CC_1_INDEX);
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, compare, DL_TIMER_CC_0_INDEX);
    }
}

void Motion_Set_Pwm(int16_t motor_1, int16_t motor_2,
                    int16_t motor_3, int16_t motor_4)
{
    Motor_Set_Pwm(Motor_M1, motor_1);
    Motor_Set_Pwm(Motor_M2, motor_2);
    Motor_Set_Pwm(Motor_M3, motor_3);
    Motor_Set_Pwm(Motor_M4, motor_4);
}

void Motor_Set_Pwm(uint8_t id, int16_t speed)
{
    /* Clamp first so -INT16_MIN and the dead-zone addition cannot overflow. */
    if (speed > MOTOR_MAX_PULSE) {
        speed = MOTOR_MAX_PULSE;
    } else if (speed < -MOTOR_MAX_PULSE) {
        speed = -MOTOR_MAX_PULSE;
    }

    const uint8_t forward = (speed >= 0) ? 1U : 0U;
    int16_t magnitude = forward ? speed : (int16_t)-speed;

    if (magnitude != 0) {
        magnitude += MOTOR_IGNORE_PULSE;
        if (magnitude > MOTOR_MAX_PULSE) {
            magnitude = MOTOR_MAX_PULSE;
        }
    }

    switch (id) {
    case Motor_M1:
        L1_control((uint16_t)magnitude, forward);
        break;
    case Motor_M2:
        L2_control((uint16_t)magnitude, forward);
        break;
    case Motor_M3:
        R1_control((uint16_t)magnitude, forward);
        break;
    case Motor_M4:
        R2_control((uint16_t)magnitude, forward);
        break;
    default:
        break;
    }
}
