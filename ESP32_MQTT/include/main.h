#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

typedef struct 
{
    uint8_t temp;
    uint8_t humi;
    uint8_t airt;
    uint8_t fume;
    bool fire;
    uint8_t air_ts;
    uint8_t fume_ts;
    uint8_t power;
} Receive_Value_Struct;

extern Receive_Value_Struct Receive_VS;

typedef struct
{
    uint8_t air_ts;
    uint8_t fume_ts;
} Transmit_Value_Struct;

extern Transmit_Value_Struct Transmit_VS;

#endif