#ifndef MQ135_AIR_SENSOR_H
#define MQ135_AIR_SENSOR_H

#include "board.h"

void MQ135AS_Init(void);
uint8_t MQ135AS_Read(uint8_t *air);

#endif