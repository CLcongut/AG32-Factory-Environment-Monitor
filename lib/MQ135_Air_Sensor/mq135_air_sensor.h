#ifndef MQ135_AIR_SENSOR_H
#define MQ135_AIR_SENSOR_H

#define MQ135_CHANNEL ADC_CHANNEL4
#define MQ135_ADC ADC0

void MQ135AS_Init(void);
uint8_t MQ135AS_Read(uint8_t *air);

#endif