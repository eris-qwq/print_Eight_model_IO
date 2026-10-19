#include "bsp_enconder.h"

volatile uint32_t gpioA;
volatile int32_t gEncoderCount_L1 = 0;
volatile int32_t gEncoderCount_L2 = 0;
volatile int32_t gEncoderCount_R1 = 0;
volatile int32_t gEncoderCount_R2 = 0;
 
void GROUP1_IRQHandler(void)
{
    //��ȡ�ж��ź�
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
    L1_Enconder_A_pin_14_PIN | L1_Enconder_B_pin_15_PIN|
		L2_Enconder_A_pin_24_PIN|L2_Enconder_B_pin_25_PIN|
		R1_Enconder_A_pin_8_PIN|R1_Enconder_B_pin_9_PIN|
		R2_Enconder_A_pin_21_PIN|R2_Enconder_B_pin_22_PIN);
	
//-------------------------------------------------��ߵ��----------------------------------------------- 
  //L1  
	if((gpioA & L1_Enconder_A_pin_14_PIN) == L1_Enconder_A_pin_14_PIN)
	{
			//Pin14�����أ���Pin15�ĵ�ƽ��Ϊ�͵�ƽ���ж�Ϊ��ת���ߵ�ƽ�ж�Ϊ��ת
			if(!DL_GPIO_readPins(GPIOA,L1_Enconder_B_pin_15_PIN))//P15Ϊ�͵�ƽ
			{
					gEncoderCount_L1--;
			}
			else//P15Ϊ�ߵ�ƽ
			{
					gEncoderCount_L1++;
			}
	}
	
	else if((gpioA & L1_Enconder_B_pin_15_PIN) == L1_Enconder_B_pin_15_PIN)
	{
			//Pin15������
			if(!DL_GPIO_readPins(GPIOA,L1_Enconder_A_pin_14_PIN))//P14Ϊ�͵�ƽ
			{
					gEncoderCount_L1++;
			}
			else//P14Ϊ�ߵ�ƽ
			{
					gEncoderCount_L1--;
			}
	}
		
	//L2 
	if((gpioA & L2_Enconder_A_pin_24_PIN) == L2_Enconder_A_pin_24_PIN)
	{
			//Pin24�����أ���Pin25�ĵ�ƽ��Ϊ�͵�ƽ���ж�Ϊ��ת���ߵ�ƽ�ж�Ϊ��ת
			if(!DL_GPIO_readPins(GPIOA,L2_Enconder_B_pin_25_PIN))//P25Ϊ�͵�ƽ
			{
					gEncoderCount_L2--;
			}
			else//P25Ϊ�ߵ�ƽ
			{
					gEncoderCount_L2++;
			}
	}
	
	else if((gpioA & L2_Enconder_B_pin_25_PIN) == L2_Enconder_B_pin_25_PIN)
	{
			//Pin25������
			if(!DL_GPIO_readPins(GPIOA,L2_Enconder_A_pin_24_PIN))//P24Ϊ�͵�ƽ
			{
					gEncoderCount_L2++;
			}
			else//P24Ϊ�ߵ�ƽ
			{
					gEncoderCount_L2--;
			}
	}
	
//------------------------------------------�ұߵ��-----------------------------------------
	//R1
	if((gpioA & R1_Enconder_A_pin_8_PIN) == R1_Enconder_A_pin_8_PIN)
	{
			//Pin8�����أ���Pin9�ĵ�ƽ��Ϊ�͵�ƽ���ж�Ϊ��ת���ߵ�ƽ�ж�Ϊ��ת
			if(!DL_GPIO_readPins(GPIOA,R1_Enconder_B_pin_9_PIN))//P9Ϊ�͵�ƽ
			{
					gEncoderCount_R1--;
			}
			else//P9Ϊ�ߵ�ƽ
			{
					gEncoderCount_R1++;
			}
	}
	
	else if((gpioA & R1_Enconder_B_pin_9_PIN) == R1_Enconder_B_pin_9_PIN)
	{
			//Pin9������
			if(!DL_GPIO_readPins(GPIOA,R1_Enconder_A_pin_8_PIN))//P8Ϊ�͵�ƽ
			{
					gEncoderCount_R1++;
			}
			else//P8Ϊ�ߵ�ƽ
			{
					gEncoderCount_R1--;
			}
	}
	
	//R2
	if((gpioA & R2_Enconder_A_pin_21_PIN) == R2_Enconder_A_pin_21_PIN)
	{
			//Pin21�����أ���Pin22�ĵ�ƽ��Ϊ�͵�ƽ���ж�Ϊ��ת���ߵ�ƽ�ж�Ϊ��ת
			if(!DL_GPIO_readPins(GPIOA,R2_Enconder_B_pin_22_PIN))//P22Ϊ�͵�ƽ
			{
					gEncoderCount_R2--;
			}
			else//P22Ϊ�ߵ�ƽ
			{
					gEncoderCount_R2++;
			}
	}
	
	else if((gpioA & R2_Enconder_B_pin_22_PIN) == R2_Enconder_B_pin_22_PIN)
	{
			//Pin22������
			if(!DL_GPIO_readPins(GPIOA,R2_Enconder_A_pin_21_PIN))//P21Ϊ�͵�ƽ
			{
					gEncoderCount_R2++;
			}
			else//P21Ϊ�ߵ�ƽ
			{
					gEncoderCount_R2--;
			}
	}
	
	
	
	
    
	//�������жϱ�־λ
	//����
	DL_GPIO_clearInterruptStatus(GPIOA, L1_Enconder_A_pin_14_PIN|L1_Enconder_B_pin_15_PIN);
	DL_GPIO_clearInterruptStatus(GPIOA, L2_Enconder_A_pin_24_PIN|L2_Enconder_B_pin_25_PIN);
	
	//�ҵ��
	DL_GPIO_clearInterruptStatus(GPIOA, R1_Enconder_A_pin_8_PIN|R1_Enconder_B_pin_9_PIN);
	DL_GPIO_clearInterruptStatus(GPIOA, R2_Enconder_A_pin_21_PIN|R2_Enconder_B_pin_22_PIN);

		
}