#include "app_irtracking.h"

#include "bsp_at8236.h"
#include "bsp_usart.h"
#include "ti_msp_dl_config.h"

static int16_t clamp_pwm(int16_t pwm)
{
    if (pwm < 0) {
        return 0;
    }
    if (pwm > IR_TRACKING_MAX_PWM) {
        return IR_TRACKING_MAX_PWM;
    }
    return pwm;
}

uint8_t IRTracking_ReadRaw(void)
{
    return (uint8_t)(
        ((DL_GPIO_readPins(IR_X_X1_PORT, IR_X_X1_PIN) != 0U) << 7) |
        ((DL_GPIO_readPins(IR_X_X2_PORT, IR_X_X2_PIN) != 0U) << 6) |
        ((DL_GPIO_readPins(IR_X_X3_PORT, IR_X_X3_PIN) != 0U) << 5) |
        ((DL_GPIO_readPins(IR_X_X4_PORT, IR_X_X4_PIN) != 0U) << 4) |
        ((DL_GPIO_readPins(IR_X_X5_PORT, IR_X_X5_PIN) != 0U) << 3) |
        ((DL_GPIO_readPins(IR_X_X6_PORT, IR_X_X6_PIN) != 0U) << 2) |
        ((DL_GPIO_readPins(IR_X_X7_PORT, IR_X_X7_PIN) != 0U) << 1) |
        ((DL_GPIO_readPins(IR_X_X8_PORT, IR_X_X8_PIN) != 0U) << 0));
}

IRTrackingState IRTracking_Compute(uint8_t raw_bits)
{
    static const int8_t position[8] = {-7, -5, -3, -1, 1, 3, 5, 7};
    IRTrackingState state = {.raw_bits = raw_bits};
    uint8_t count = 0U;
    int16_t sum = 0;

    for (uint8_t sensor = 0U; sensor < 8U; ++sensor) {
        const uint8_t level = (raw_bits >> (7U - sensor)) & 1U;
        if (level == IR_TRACKING_ACTIVE_LEVEL) {
            sum += position[sensor];
            ++count;
        }
    }

    /* A completely lost line stops the vehicle until a sensor sees it again. */
    if (count == 0U) {
        return state;
    }

    state.line_found = 1U;
    state.error = (int8_t)(sum / count);
    const int16_t correction = (int16_t)state.error * IR_TRACKING_TURN_GAIN;
    state.left_pwm = clamp_pwm(IR_TRACKING_BASE_PWM + correction);
    state.right_pwm = clamp_pwm(IR_TRACKING_BASE_PWM - correction);
    return state;
}

static void send_number(int16_t value)
{
    char digits[6];
    uint8_t length = 0U;
    uint16_t magnitude;

    if (value < 0) {
        uart0_send_char('-');
        magnitude = (uint16_t)(-value);
    } else {
        magnitude = (uint16_t)value;
    }

    do {
        digits[length++] = (char)('0' + (magnitude % 10U));
        magnitude /= 10U;
    } while (magnitude != 0U);

    while (length != 0U) {
        uart0_send_char(digits[--length]);
    }
}

static void send_report(const IRTrackingState *state)
{
    uart0_send_string("IR:");
    for (uint8_t bit = 0U; bit < 8U; ++bit) {
        uart0_send_char((char)('0' + ((state->raw_bits >> (7U - bit)) & 1U)));
    }
    uart0_send_string(",VALID:");
    send_number(state->line_found);
    uart0_send_string(",ERR:");
    send_number(state->error);
    uart0_send_string(",L:");
    send_number(state->left_pwm);
    uart0_send_string(",R:");
    send_number(state->right_pwm);
    uart0_send_string("\r\n");
}

void LineWalking(void)
{
    static uint8_t report_counter = 0U;
    const IRTrackingState state = IRTracking_Compute(IRTracking_ReadRaw());

    // Motor_Set_Pwm(Motor_M1, IR_TRACKING_L1_FORWARD_SIGN * state.left_pwm);
    // Motor_Set_Pwm(Motor_M3, IR_TRACKING_R1_FORWARD_SIGN * state.right_pwm);

    if (++report_counter >= IR_TRACKING_REPORT_EVERY) {
        report_counter = 0U;
        send_report(&state);
    }
}
