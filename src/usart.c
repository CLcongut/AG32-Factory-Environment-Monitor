#include "main.h"
#include "usart.h"

#define addrss 0x37

volatile char isRecvEnd = 0; // 是否收取idle完整一包
volatile char rcvLen = 0;    // rx收取的包的长度
char rxbuf[64];              // rx收取的缓存buff
char txbuf[15];
void UART1_isr()
{
    if (UART_IsRawIntActive(UART1, UART_INT_RX))
    {
        UART_ClearInt(UART1, UART_INT_RX);
        // 注意：这时FIFO里有8个字节长度，但特意不全部收取。
        // 这么做，是为了保证传输数据刚好是8的整数倍时，仍然会触发下边的UART_INT_RT中断。
        UART_Receive(UART1, rxbuf + rcvLen, 7, 0); // half: 16/2=8。
        rcvLen += 7;
    }
    else if (UART_IsRawIntActive(UART1, UART_INT_RT))
    {
        UART_ClearInt(UART1, UART_INT_RT);
        rcvLen += UART_Receive(UART1, rxbuf + rcvLen, 8, 1); // 最后一个参数不能为0，为0时UART_Receive是不会超时退出的
        isRecvEnd = 1;                                       // idle一包收满
    }
    txbuf[0] = addrss;
}

void S_USART_Init(void)
{
    GPIO_AF_ENABLE(UART1_UARTRXD);
    GPIO_AF_ENABLE(UART1_UARTTXD);
    SYS_EnableAPBClock(APB_MASK_UART1);
    UART_Init(UART1, 115200, UART_LCR_DATABITS_8, UART_LCR_STOPBITS_1, UART_LCR_PARITY_NONE, UART_LCR_FIFO_16);

    UART_EnableInt(UART1, UART_INT_RT);                // 配置 收超时中断
    UART_EnableInt(UART1, UART_INT_RX);                // 配置 收中断
    UART_SetRxIntFifoLevel(UART1, UART_INT_FIFO_HALF); // 配置FIFO收多少字节时产生收中断
    INT_EnableIRQ(UART1_IRQn, UART_PRIORITY);

    UART_Send(UART1, "test idleIrq\r\n", strlen("test idleIrq\r\n"));
}

void S_USART_Trans(void)
{
    txbuf[1] = ',';
    txbuf[2] = TaskVST.dht11_buf[2]; // 温度整数
    txbuf[3] = ',';
    txbuf[4] = TaskVST.dht11_buf[0]; // 湿度整数
    txbuf[5] = ',';
    txbuf[6] = TaskVST.mq135_buf[0]; // 空气整数
    txbuf[7] = ',';
    txbuf[8] = TaskVST.mq2_buf[0]; // 烟雾整数
    txbuf[9] = ',';
    txbuf[10] = TaskVST.fire_state;
    UART_Send(UART1, txbuf, strlen(txbuf));
}