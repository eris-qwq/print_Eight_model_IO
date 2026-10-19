#ifndef __BSP_TB6612_H_
#define __BSP_TB6612_H_


#include <stdint.h>

#define MOTOR_IGNORE_PULSE  (60)  //60
#define MOTOR_MAX_PULSE     (1000 -1)


void init_motor(void);

void L1_control(uint16_t motor_speed,uint8_t dir);
void L2_control(uint16_t motor_speed,uint8_t dir);
void R1_control(uint16_t motor_speed,uint8_t dir);
void R2_control(uint16_t motor_speed,uint8_t dir);


void Motion_Set_Pwm(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
void Motor_Set_Pwm(uint8_t id, int16_t speed);

// MOTOR: M1 M2 M3 M4
// MOTOR: L1 L2 R1 R2
typedef enum
{
	Motor_M1 = 0,
	Motor_M2 ,
	Motor_M3 ,
	Motor_M4 ,
	Motor_MAX
}Motor_ID;


#endif

