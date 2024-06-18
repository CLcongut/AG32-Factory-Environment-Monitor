#include "main.h"
#include "usart.h"

#define HEAD 0xAA
#define ADDRESS 0x37
#define CMD 0x01
#define DATACNT 8
#define DATALEN DATACNT + 5

volatile char isRecvEnd = 0; // 是否收取idle完整一包
volatile char rcvLen = 0;    // rx收取的包的长度
char rxbuf[64];              // rx收取的缓存buff
char txbuf[DATALEN];
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
    // SYS_EnableAPBClock(APB_MASK_GPIO1);
    // GPIO_SetOutput(GPIO1, GPIO_BIT0);
    // GPIO_SetLow(GPIO1, GPIO_BIT0);
}

uint8_t CheckSum(uint8_t *Buf, uint8_t Len)
{
    uint8_t i = 0;
    uint8_t sum = 0;
    uint8_t checksum = 0;

    for (i = 0; i < Len; i++)
    {
        sum += *Buf++;
    }

    checksum = sum & 0xff;

    return checksum;
}

void S_USART_Trans(void)
{
    txbuf[0] = HEAD;
    txbuf[1] = ADDRESS;
    txbuf[2] = CMD;
    txbuf[3] = DATACNT;
    txbuf[4] = TaskVST.dht11_buf[2]; // 温度整数
    txbuf[5] = TaskVST.dht11_buf[0]; // 湿度整数
    txbuf[6] = TaskVST.mq135_buf[0]; // 空气整数
    txbuf[7] = TaskVST.mq2_buf[0];   // 烟雾整数
    txbuf[8] = TaskVST.fire_curr_state;
    txbuf[9] = TaskVST.power;
    txbuf[10] = TaskTST.air_V;
    txbuf[11] = TaskTST.fume_V;
    uint8_t *pcheck = txbuf + 4;
    txbuf[12] = CheckSum(pcheck, DATACNT);
    UART_Send(UART1, txbuf, DATALEN);
}

void S_USART_Recev(void)
{
    if (isRecvEnd == 1)
    {
        UART_Send(UART1, rxbuf, rcvLen);
        UART_Send(UART1, "\r\n", strlen("\r\n"));
        if (rxbuf[2] == 0x02)
        {
            TaskTST.air_V = rxbuf[4];
            TaskTST.fume_V = rxbuf[5];
        }
        rcvLen = 0;
        isRecvEnd = 0;
    }
}