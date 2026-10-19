#include "bsp_usart.h"
#include "ti_msp_dl_config.h"
//#include "stdio.h"
volatile unsigned char uart_data = 0;

//#if !defined(__MICROLIB)
////不使用微库的话就需要添加下面的函数
//#if (__ARMCLIB_VERSION <= 6000000)
////如果编译器是AC5  就定义下面这个结构体
//struct __FILE
//{
//        int handle;
//};
//#endif
//FILE __stdout;
////定义_sys_exit()以避免使用半主机模式
//void _sys_exit(int x)
//{
//        x = x;
//}
//#endif
//int fputc(int ch, FILE *stream)
//{
//        while( DL_UART_isBusy(MYUART_INST) == true );

//        DL_UART_Main_transmitData(MYUART_INST, ch);

//        return ch;
//}

//串口发送单个字符
void uart0_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(MYUART_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(MYUART_INST, ch);
}
//串口发送字符串
void uart0_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_send_char(*str++);
    }
}


//串口的中断服务函数
void MYUART_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(MYUART_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //接发送过来的数据保存在变量中
            uart_data = DL_UART_Main_receiveData(MYUART_INST);
            //将保存的数据再发送出去
//            uart0_send_char(uart_data);
				
					  //Deal_IR_Usart(uart_data);//红外探头数据处理
            break;

        default://其他的串口中断
            break;
    }
}