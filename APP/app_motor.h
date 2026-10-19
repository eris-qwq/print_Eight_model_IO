#ifndef __APP_MOTOR_H_
#define __APP_MOTOR_H_

#include <stdint.h>




#define MOTOR_P  (1.3f)
#define MOTOR_I  (0.08f)
#define MOTOR_D  (0.5f)

#define PI      (3.1415926f)

// 450RPM 时，电机转一圈对应的编码器脉冲数，计算方式：电机转速 × 轮周长 × 2 × 传动比（20*13*2）
#define ENCODER_CIRCLE_450           (520.0f) // 1040

// 小车轴距，左右轮中心距离之和的一半
#define STM32Car_APB                  (150.0f)

// 车轮转一圈的线位移，单位为毫米
#define WHEEL_CIRCLE_MM            (204.203f)


typedef struct _pid
{
    float target_val;               // 目标值
    float output_val;               // 输出值
    float pwm_output;               // PWM输出值
    float Kp,Ki,Kd;                 // 比例、积分、微分系数
    float err;                      // 当前偏差值
    float err_last;                 // 上一次偏差值

    float err_next;                 // 下一次偏差值，增量式
    float integral;                 // 积分累计值
} pid_t;


typedef struct _motor_data_t
{
    float speed_mm_s[4];        // 各电机当前线速度，单位 mm/s
    float speed_pwm[4];         // 各电机经过PID计算后的PWM值
    int16_t speed_set[4];       // 目标速度设定值
} motor_data_t;

typedef struct _car_data
{
    int16_t Vx;
    int16_t Vy;
    int16_t Vz;
} car_data_t;

// 编码器相关函数
void Encoder_Get_ALL(int* Encoder_all);
void Motion_Get_Encoder(void);

// PID相关函数
void Motor_PID_Init(void);
void PID_Set_Motor_Target(uint8_t motor_id, float target);
void PID_Clear_Motor(uint8_t motor_id);
float PID_Incre_Calc(pid_t *pid, float actual_val);
void PID_Calc_Motor(motor_data_t* motor);

// 运动控制相关函数
void Motion_Set_Speed(int16_t speed_m1, int16_t speed_m2, int16_t speed_m3, int16_t speed_m4);
void Motion_Get_Speed(car_data_t* car);
void Motion_Stop(void);
void wheel_Ctrl(int16_t V_x, int16_t V_y, int16_t V_z);
void Motion_Handle(void);
void motion_car_control(int16_t V_x, int16_t V_y, int16_t V_z);


#endif

