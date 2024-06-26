/***************************************************************************************
 * Encoding with UTF-8
 * ADC 引脚固定，无法在 ve文件中更改,具体ADC引脚参考 AG32 手册
 * 文件中凡是带有 IO 字段的，都可以被配置
 * 如果一路 ADC 引脚已经被 ADC 使用，那么此管脚只能用于这路 ADC，
 * 如果没有被 ADC 使能，那仍然可以被配置用于其他功能
 *
 * ADC/DAC 包含模拟电路，需要 fpga 部分的支持
 * 在默认的 ip 中，支持 3 路 ADC 和 2 路 DAC，1 路比较器 CMP（双通道，可独立运行）
 * ADC 不需要在 ve 里管脚映射，不需要设置 IO 复用
 *
 * 使用时在 ini文件中配置：(大约在112行)
 * ip_name = analog_ip
 * 注意，第一次打开 ADC/DAC 功能时，需要重新编译烧录一次 ve
 *
 * 此为MQ-2烟雾传感器驱动，可检测丙烷，烟雾等多种可燃性气体
 *
 * 目前版本为：1.0
 * Encoding with UTF-8
 ***************************************************************************************
 */

#include "board.h"
#include "analog_ip.h"
#include "mq2_fumes_sensor.h"

static uint32_t sclk_div = 9; // Divided by 20 = (9 + 1) * 2

/**
 * @brief mq2 烟雾传感器初始化
 *
 */
void MQ2FS_Init(void)
{
    ADC_SetChannel(MQ2_ADC, MQ2_CHANNEL);
}

/**
 * @brief mq2 烟雾传感器数据读取
 *
 * @return uint32_t 烟雾传感器数据
 */
uint8_t MQ2FS_Read(uint8_t *fume)
{
    ADC_SetChannel(MQ2_ADC, MQ2_CHANNEL);
    uint32_t mq2_value = 0;
    uint8_t *data = fume;
    for (uint8_t i = 0; i < 50; i++)
    {
        ADC_Start(MQ2_ADC, sclk_div);
        ADC_WaitForEoc(MQ2_ADC);
        mq2_value += ADC_GetData(MQ2_ADC);
    }
    mq2_value = mq2_value * 200 / 4096;
    data[0] = mq2_value / 100;
    data[1] = mq2_value % 100;
    return 1;
}
