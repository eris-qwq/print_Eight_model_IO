#include "app_motor.h"
#include "bsp_at8236.h"


extern volatile int32_t gEncoderCount_L1,gEncoderCount_L2;
extern volatile int32_t gEncoderCount_R1 ,gEncoderCount_R2;

pid_t pid_motor[4];

int Encoder_speed_offset[4] = {0};
int Encoder_speed_last[4] = {0};
int Encoder_speed_now[4] = {0};

uint8_t g_start_ctrl = 0;
car_data_t car_data;
motor_data_t motor_data;

// 读取本次采样周期内的四个轮子编码器增量，并清零累积计数。
// 这里使用“增量法”来计算每个轮子的速度变化，避免累计误差。
void Encoder_Get_ALL(int* Encoder_all)
{
			/* 左轮计数器取差值，右轮计数器取差值并按正方向累加 */
			Encoder_all[0] -= gEncoderCount_L1;
			Encoder_all[1] -= gEncoderCount_L2;
			
			Encoder_all[2] += gEncoderCount_R1;
			Encoder_all[3] += gEncoderCount_R2;
			
			gEncoderCount_L1 = 0; /* 清零左轮累计计数 */
			gEncoderCount_L2 = 0; /* 清零左轮累计计数 */
			gEncoderCount_R1 = 0; /* 清零右轮累计计数 */
			gEncoderCount_R2 = 0; /* 清零右轮累计计数 */
}

// 读取本周期编码器变化量，并计算各轮当前速度偏移值。
// Encoder_speed_offset 表示本采样周期内轮子转过的脉冲数，用于换算成 mm/s。
void Motion_Get_Encoder(void)
{
    Encoder_Get_ALL(Encoder_speed_now);

    for(uint8_t i = 0; i < Motor_MAX; i++)
    {
        // 记录本次与上次采样之间的脉冲变化量
        Encoder_speed_offset[i] = Encoder_speed_now[i] - Encoder_speed_last[i];
	    // 保存上一轮采样值，供下一周期做差分
	    Encoder_speed_last[i] = Encoder_speed_now[i];
    
    }
}


// 返回编码器一圈对应的脉冲数，用于将脉冲转成轮速。
static  float Motion_Get_Circle_Pulse(void)
{  
    return ENCODER_CIRCLE_450;
}

// 返回当前底盘的轴距参数，用于计算角速度。
static float Motion_Get_APB(void)
{
    return STM32Car_APB;
}

// 返回轮子一圈所对应的车轮周长，单位为毫米。
static float Motion_Get_Circle_MM(void)
{
		return WHEEL_CIRCLE_MM; 
}



// 初始化四个电机的PID参数和状态变量。
// target_val 保存目标速度，pwm_output 保存输出给电机的PWM/速度控制值。
void Motor_PID_Init(void)
{
	for (int i = 0; i < Motor_MAX; i++)
	{
			pid_motor[i].target_val = 0.0;
			pid_motor[i].pwm_output = 0.0;
			pid_motor[i].err = 0.0;
			pid_motor[i].err_last = 0.0;
			pid_motor[i].err_next = 0.0;
			pid_motor[i].integral = 0.0;

			pid_motor[i].Kp = MOTOR_P;
			pid_motor[i].Ki = MOTOR_I;
			pid_motor[i].Kd = MOTOR_D;
	}


}


// 设置指定电机或全部电机的目标速度，单位为 mm/s
void PID_Set_Motor_Target(uint8_t motor_id, float target)
{
    if (motor_id > Motor_MAX) return;

    if (motor_id == Motor_MAX)
    {
        for (int i = 0; i < Motor_MAX; i++)
        {
            pid_motor[i].target_val = target;
        }
    }
    else
    {
        pid_motor[motor_id].target_val = target;
    }
}

// 清除指定电机的PID状态量，恢复到初始空白状态
void PID_Clear_Motor(uint8_t motor_id)
{
    if (motor_id > Motor_MAX) return;

    if (motor_id == Motor_MAX)
    {
        for (int i = 0; i < Motor_MAX; i++)
        {
            pid_motor[i].pwm_output = 0.0;
            pid_motor[i].err = 0.0;
            pid_motor[i].err_last = 0.0;
            pid_motor[i].err_next = 0.0;
            pid_motor[i].integral = 0.0;
        }
    }
    else
    {
        pid_motor[motor_id].pwm_output = 0.0;
        pid_motor[motor_id].err = 0.0;
        pid_motor[motor_id].err_last = 0.0;
        pid_motor[motor_id].err_next = 0.0;
        pid_motor[motor_id].integral = 0.0;
    }
}



// 增量式PID控制器核心计算函数。
// 误差 = 目标速度 - 实际速度，然后按增量公式更新控制量，适合速度环闭环控制。
float PID_Incre_Calc(pid_t *pid, float actual_val)
{
    /* 计算当前误差 */
    pid->err = pid->target_val - actual_val;
    /* 采用增量式PID算法实现：P差分 + I累积 + D微分 */
    pid->pwm_output += pid->Kp *(pid->err - pid->err_next) 
                    + pid->Ki  * pid->err 
                    + pid->Kd  *(pid->err - 2 * pid->err_next + pid->err_last);
    /* 保存误差历史值，用于下一次迭代 */
    pid->err_last = pid->err_next;
    pid->err_next = pid->err;
    
    /* 对输出做限幅，避免PWM超出电机驱动允许范围 */

		if (pid->pwm_output > (MOTOR_MAX_PULSE-MOTOR_IGNORE_PULSE))
				pid->pwm_output = (MOTOR_MAX_PULSE-MOTOR_IGNORE_PULSE);
		if (pid->pwm_output < (MOTOR_IGNORE_PULSE-MOTOR_MAX_PULSE))
				pid->pwm_output = (MOTOR_IGNORE_PULSE-MOTOR_MAX_PULSE);

    return pid->pwm_output;
}


// 遍历四个电机，将实际速度误差转成各自的PWM控制输出。
void PID_Calc_Motor(motor_data_t* motor)
{
    int i;
       
    for (i = 0; i < Motor_MAX; i++)
    {
        motor->speed_pwm[i] = PID_Incre_Calc(&pid_motor[i], motor->speed_mm_s[i]);
    }
}



// 设置四个轮子的目标速度，供PID闭环跟踪。
// 当输入四轮均为0时，直接执行停止逻辑，避免PID继续控制导致“死锁/失控”状态。
void Motion_Set_Speed(int16_t speed_m1, int16_t speed_m2, int16_t speed_m3, int16_t speed_m4)
{
		if(speed_m1 == 0 && speed_m2 == 0 && speed_m3 == 0 && speed_m4 ==0)
		{
				 Motion_Stop();
            return;
		}
		else
		{
			// 由于电机存在死区/空转特性，如果只判断某个单轮为0，PID控制会导致停止状态异常。
			// 因此这里使用统一状态标志来保持控制启用。
				g_start_ctrl = 1;
		}
			
			
    motor_data.speed_set[0] = speed_m1;
    motor_data.speed_set[1] = speed_m2;
    motor_data.speed_set[2] = speed_m3;
    motor_data.speed_set[3] = speed_m4;
    for (uint8_t i = 0; i < Motor_MAX; i++)
    {
        PID_Set_Motor_Target(i, motor_data.speed_set[i]*1.0);
    }
}


// 从编码器计数中换算当前车体速度，单位为 mm/s。
// 采用脉冲数 × 周长 / 一圈脉冲数 × 100 的方式得到轮速，随后再计算车体线速度与角速度。
void Motion_Get_Speed(car_data_t* car)
{
    int i = 0;
    float speed_mm[Motor_MAX] = {0};
    float circle_mm = Motion_Get_Circle_MM();
    float circle_pulse = Motion_Get_Circle_Pulse();
    float robot_APB = Motion_Get_APB();

    Motion_Get_Encoder();

    // 把编码器增量换算成各轮线速度，单位为 mm/s。
    for (i = 0; i < 4; i++)
    {
        speed_mm[i] = (Encoder_speed_offset[i]) * 100 * circle_mm / circle_pulse;
        motor_data.speed_mm_s[i] = speed_mm[i];
    }
		
		 car->Vx = (speed_mm[0] + speed_mm[1] + speed_mm[2] + speed_mm[3]) / 4;
     car->Vy = 0;
     car->Vz = -(speed_mm[0] + speed_mm[1] - speed_mm[2] - speed_mm[3]) / 4.0f / robot_APB * 1000;
		
		if (g_start_ctrl)
    {
        PID_Calc_Motor(&motor_data);
		}
}

// 车体急停函数：清零所有电机目标速度并重置PID状态，然后直接输出零PWM。
void Motion_Stop(void)
{
    for (uint8_t i = 0; i < Motor_MAX; ++i) {
        motor_data.speed_set[i] = 0;
        pid_motor[i].target_val = 0.0f;
    }
    PID_Clear_Motor(Motor_MAX);
    g_start_ctrl = 0;
	
    Motion_Set_Pwm(0,0,0,0);
}


static float speed_lr = 0;
static float speed_fb = 0;
static float speed_spin = 0;
static int speed_L1_setup = 0;
static int speed_L2_setup = 0;
static int speed_R1_setup = 0;
static int speed_R2_setup = 0;

// 底盘速度分解函数：将整体运动指令 Vx/Vy/Vz 转换为四个轮子的目标速度。
// 这里 V_x 为前后速度，V_z 为绕Z轴转角速度，V_y 当前未使用。
void wheel_Ctrl(int16_t V_x, int16_t V_y, int16_t V_z)
{
    float robot_APB = Motion_Get_APB();
//    speed_lr = -V_y;
		speed_lr = 0;
    speed_fb = V_x;
    speed_spin = (V_z / 1000.0f) * robot_APB;
    if (V_x == 0 && V_y == 0 && V_z == 0)
    {
        Motion_Stop();
        return;
    }

    speed_L1_setup = speed_fb + speed_lr + speed_spin;
    speed_L2_setup = speed_fb - speed_lr + speed_spin;
    speed_R1_setup = speed_fb - speed_lr - speed_spin;
    speed_R2_setup = speed_fb + speed_lr - speed_spin;
		
		if (speed_L1_setup > 1000) speed_L1_setup = 1000;
		if (speed_L1_setup < -1000) speed_L1_setup = -1000;
		if (speed_L2_setup > 1000) speed_L2_setup = 1000;
		if (speed_L2_setup < -1000) speed_L2_setup = -1000;
		if (speed_R1_setup > 1000) speed_R1_setup = 1000;
		if (speed_R1_setup < -1000) speed_R1_setup = -1000;
		if (speed_R2_setup > 1000) speed_R2_setup = 1000;
		if (speed_R2_setup < -1000) speed_R2_setup = -1000;
		
		//printf("%d\t,%d\t,%d\t,%d\r\n",speed_L1_setup,speed_L2_setup,speed_R1_setup,speed_R2_setup);
		
		Motion_Set_Speed(speed_L1_setup, speed_L2_setup, speed_R1_setup, speed_R2_setup);
		
	}
		
		
// 运动控制主处理函数，通常按固定周期（如10ms）调度。
// 先读取当前轮速，再在控制已开启时更新四个电机PWM，形成闭环速度控制。
void Motion_Handle(void)
{
    Motion_Get_Speed(&car_data);

    if (g_start_ctrl)
    {
        Motion_Set_Pwm(motor_data.speed_pwm[0], motor_data.speed_pwm[1], motor_data.speed_pwm[2], motor_data.speed_pwm[3]);
    }
}


// 直接控制四轮PWM输出的简化接口，适合手动测试或开环控制。
// V_x 为前后速度，V_z 为旋转速度，Y方向未启用。
void motion_car_control(int16_t V_x, int16_t V_y, int16_t V_z)
{
    (void)V_y; /* Lateral motion is not supported by this chassis. */
	float robot_APB = Motion_Get_APB();
		speed_lr = 0;
    speed_fb = V_x;
    speed_spin = (V_z / 1000.0f) * robot_APB;
    if (V_x == 0  && V_z == 0)
    {
        Motion_Set_Pwm(0,0,0,0);
        return;
    }

    speed_L1_setup = speed_fb + speed_spin;
    speed_L2_setup = speed_fb + speed_spin;
    speed_R1_setup = speed_fb  - speed_spin;
    speed_R2_setup = speed_fb  - speed_spin;
		
		if (speed_L1_setup > 1000) speed_L1_setup = 1000;
		if (speed_L1_setup < -1000) speed_L1_setup = -1000;
		if (speed_L2_setup > 1000) speed_L2_setup = 1000;
		if (speed_L2_setup < -1000) speed_L2_setup = -1000;
		if (speed_R1_setup > 1000) speed_R1_setup = 1000;
		if (speed_R1_setup < -1000) speed_R1_setup = -1000;
		if (speed_R2_setup > 1000) speed_R2_setup = 1000;
		if (speed_R2_setup < -1000) speed_R2_setup = -1000;
		
		//printf("%d\t,%d\t,%d\t,%d\r\n",speed_L1_setup,speed_L2_setup,speed_R1_setup,speed_R2_setup);
		
		Motion_Set_Pwm(speed_L1_setup, speed_L2_setup, speed_R1_setup, speed_R2_setup);
		
}



