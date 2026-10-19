#ifndef APP_IRTRACKING_H
#define APP_IRTRACKING_H

#include <stdint.h>

/* X1 is the leftmost sensor; X8 is the rightmost sensor. */
#define IR_TRACKING_ACTIVE_LEVEL       (0U)   /* 0: dark line gives a low level */
#define IR_TRACKING_PERIOD_MS          (20U)
#define IR_TRACKING_REPORT_EVERY       (5U)   /* One UART report per 100 ms */
/* The motor driver adds 60 PWM counts; 939 reaches its 999-count limit. */
#define IR_TRACKING_BASE_PWM           (939)
#define IR_TRACKING_MAX_PWM            (939)
#define IR_TRACKING_TURN_GAIN          (140)

/* Forward directions observed on the assembled chassis. */
#define IR_TRACKING_L1_FORWARD_SIGN    (-1)
#define IR_TRACKING_R1_FORWARD_SIGN    (1)

typedef struct {
    uint8_t raw_bits;       /* X1 in bit 7, X8 in bit 0 */
    uint8_t line_found;
    int8_t error;           /* Negative: line left; positive: line right */
    int16_t left_pwm;       /* Forward magnitude, before motor sign */
    int16_t right_pwm;
} IRTrackingState;

uint8_t IRTracking_ReadRaw(void);
IRTrackingState IRTracking_Compute(uint8_t raw_bits);
void LineWalking(void);

#endif
