#include "main.h"
#include "usart.h"

#define ADDRESS_T1 9238
#define ADDRESS_T2 9239
#define ADDRESS_R1 9237
#define CHANNEL 19
#define CMD 0x04
#define DATACNT 5
#define DATALEN DATACNT + 6

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

    // UART_Send(UART1, "test idleIrq\r\n", strlen("test idleIrq\r\n"));
}

void S_USART_Spawn_Radom_Data(void)
{
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
#if 0
    txbuf[0] = (uint8_t)(ADDRESS_R1 >> 8);
    txbuf[1] = (uint8_t)ADDRESS_R1;
    txbuf[2] = CHANNEL;
    txbuf[3] = CMD;
    txbuf[4] = DATACNT;
    txbuf[5] = TaskVST.dht11_buf[2]; // 温度整数
    txbuf[6] = TaskVST.dht11_buf[0]; // 湿度整数
    txbuf[7] = TaskVST.mq135_buf[0]; // 空气整数
    txbuf[8] = TaskVST.mq2_buf[0];   // 烟雾整数
    txbuf[9] = TaskVST.fire_curr_state;
    txbuf[10] = TaskVST.power;
    txbuf[11] = TaskTST.ts_temp[0];
    txbuf[12] = TaskTST.ts_temp[1];
    uint8_t *pcheck = txbuf + 4;
    txbuf[13] = CheckSum(pcheck, DATACNT);
    UART_Send(UART1, txbuf, DATALEN);
#endif
}

void S_USART_Fake_Trans(void)
{
    srand(read_csr(mcycle));
    txbuf[0] = (uint8_t)(ADDRESS_R1 >> 8);
    txbuf[1] = (uint8_t)ADDRESS_R1;
    txbuf[2] = CHANNEL;
    txbuf[3] = CMD;
    txbuf[4] = DATACNT;
    txbuf[5] = (random() * 100) / 255; // 温度整数
    txbuf[6] = (random() * 100) / 255; // 湿度整数
    txbuf[7] = (random() * 100) / 255; // 空气整数
    txbuf[8] = (random() * 100) / 255; // 烟雾整数
    txbuf[9] = (random() * 100) / 255;
    uint8_t *pcheck = txbuf + 4;
    txbuf[10] = CheckSum(pcheck, DATACNT);
    UART_Send(UART1, txbuf, DATALEN);
}

void S_USART_Recev(void)
{
    if (isRecvEnd == 1)
    {
        // UART_Send(UART1, rxbuf, rcvLen);
        // UART_Send(UART1, "\r\n", strlen("\r\n"));
        if (rxbuf[0] == 0x02)
        {
            TaskTST.air_V = rxbuf[2];
            TaskTST.fume_V = rxbuf[3];
        }
        else if (rxbuf[0] == 0x03)
        {
            TaskTST.air_V = rxbuf[2];
            TaskTST.fume_V = rxbuf[3];
            TaskTST.ts_temp[0] = TaskTST.air_V;
            TaskTST.ts_temp[1] = TaskTST.fume_V;
            TaskPST[6].Task_Enable_Flag = true;
            TaskPST[7].Task_Enable_Flag = true;
        }
        rcvLen = 0;
        isRecvEnd = 0;
    }
}