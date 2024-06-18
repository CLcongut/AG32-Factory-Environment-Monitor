#ifndef MQ2_FUMES_SENSOR_H
#define MQ2_FUMES_SENSOR_H

#define MQ2_CHANNEL ADC_CHANNEL3
#define MQ2_ADC ADC0

void MQ2FS_Init(void);
uint8_t MQ2FS_Read(uint8_t *fume);

#endif