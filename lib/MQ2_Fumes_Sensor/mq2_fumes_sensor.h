#ifndef MQ2_FUMES_SENSOR_H
#define MQ2_FUMES_SENSOR_H

#include "board.h"

void MQ2FS_Init(void);
uint8_t MQ2FS_Read(uint8_t *fume);

#endif