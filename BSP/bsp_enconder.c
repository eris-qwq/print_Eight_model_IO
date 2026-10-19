#include "bsp_enconder.h"

volatile uint32_t gpioA;
volatile int32_t gEncoderCount_L1 = 0;
volatile int32_t gEncoderCount_L2 = 0;
volatile int32_t gEncoderCount_R1 = 0;
volatile int32_t gEncoderCount_R2 = 0;
 
void GROUP1_IRQHandler(void)
{
    //获取中断信号
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
    L1_Enconder_A_pin_14_PIN | L1_Enconder_B_pin_15_PIN|
		L2_Enconder_A_pin_24_PIN|L2_Enconder_B_pin_25_PIN|
		R1_Enconder_A_pin_8_PIN|R1_Enconder_B_pin_9_PIN|
		R2_Enconder_A_pin_21_PIN|R2_Enconder_B_pin_22_PIN);
	
//-------------------------------------------------左边电机----------------------------------------------- 
  //L1  
	if((gpioA & L1_Enconder_A_pin_14_PIN) == L1_Enconder_A_pin_14_PIN)
	{
			//Pin14上升沿，看Pin15的电平，为低电平则判断为反转，高电平判断为正转
			if(!DL_GPIO_readPins(GPIOA,L1_Enconder_B_pin_15_PIN))//P15为低电平
			{
					gEncoderCount_L1--;
			}
			else//P15为高电平
			{
					gEncoderCount_L1++;
			}
	}
	
	else if((gpioA & L1_Enconder_B_pin_15_PIN) == L1_Enconder_B_pin_15_PIN)
	{
			//Pin15上升沿
			if(!DL_GPIO_readPins(GPIOA,L1_Enconder_A_pin_14_PIN))//P14为低电平
			{
					gEncoderCount_L1++;
			}
			else//P14为高电平
			{
					gEncoderCount_L1--;
			}
	}
		
	//L2 
	if((gpioA & L2_Enconder_A_pin_24_PIN) == L2_Enconder_A_pin_24_PIN)
	{
			//Pin24上升沿，看Pin25的电平，为低电平则判断为反转，高电平判断为正转
			if(!DL_GPIO_readPins(GPIOA,L2_Enconder_B_pin_25_PIN))//P25为低电平
			{
					gEncoderCount_L2--;
			}
			else//P25为高电平
			{
					gEncoderCount_L2++;
			}
	}
	
	else if((gpioA & L2_Enconder_B_pin_25_PIN) == L2_Enconder_B_pin_25_PIN)
	{
			//Pin25上升沿
			if(!DL_GPIO_readPins(GPIOA,L2_Enconder_A_pin_24_PIN))//P24为低电平
			{
					gEncoderCount_L2++;
			}
			else//P24为高电平
			{
					gEncoderCount_L2--;
			}
	}
	
//------------------------------------------右边电机-----------------------------------------
	//R1
	if((gpioA & R1_Enconder_A_pin_8_PIN) == R1_Enconder_A_pin_8_PIN)
	{
			//Pin8上升沿，看Pin9的电平，为低电平则判断为反转，高电平判断为正转
			if(!DL_GPIO_readPins(GPIOA,R1_Enconder_B_pin_9_PIN))//P9为低电平
			{
					gEncoderCount_R1--;
			}
			else//P9为高电平
			{
					gEncoderCount_R1++;
			}
	}
	
	else if((gpioA & R1_Enconder_B_pin_9_PIN) == R1_Enconder_B_pin_9_PIN)
	{
			//Pin9上升沿
			if(!DL_GPIO_readPins(GPIOA,R1_Enconder_A_pin_8_PIN))//P8为低电平
			{
					gEncoderCount_R1++;
			}
			else//P8为高电平
			{
					gEncoderCount_R1--;
			}
	}
	
	//R2
	if((gpioA & R2_Enconder_A_pin_21_PIN) == R2_Enconder_A_pin_21_PIN)
	{
			//Pin21上升沿，看Pin22的电平，为低电平则判断为反转，高电平判断为正转
			if(!DL_GPIO_readPins(GPIOA,R2_Enconder_B_pin_22_PIN))//P22为低电平
			{
					gEncoderCount_R2--;
			}
			else//P22为高电平
			{
					gEncoderCount_R2++;
			}
	}
	
	else if((gpioA & R2_Enconder_B_pin_22_PIN) == R2_Enconder_B_pin_22_PIN)
	{
			//Pin22上升沿
			if(!DL_GPIO_readPins(GPIOA,R2_Enconder_A_pin_21_PIN))//P21为低电平
			{
					gEncoderCount_R2++;
			}
			else//P21为高电平
			{
					gEncoderCount_R2--;
			}
	}
	
	
	
	
    
	//最后清除中断标志位
	//左电机
	DL_GPIO_clearInterruptStatus(GPIOA, L1_Enconder_A_pin_14_PIN|L1_Enconder_B_pin_15_PIN);
	DL_GPIO_clearInterruptStatus(GPIOA, L2_Enconder_A_pin_24_PIN|L2_Enconder_B_pin_25_PIN);
	
	//右电机
	DL_GPIO_clearInterruptStatus(GPIOA, R1_Enconder_A_pin_8_PIN|R1_Enconder_B_pin_9_PIN);
	DL_GPIO_clearInterruptStatus(GPIOA, R2_Enconder_A_pin_21_PIN|R2_Enconder_B_pin_22_PIN);

		
}