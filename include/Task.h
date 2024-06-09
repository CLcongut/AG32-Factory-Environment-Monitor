#ifndef TASK_H
#define TASK_H

#include "main.h"

typedef struct Task_Polling_Struct
{
    bool Task_Enable_Flag;
    uint16_t Task_Interval_Time;
    bool Task_Status_Flag;
    void (*Function_Hook)(void);
} TaskPollingStruct;

extern TaskPollingStruct TaskPST[];

typedef struct Task_Value_Struct
{
    uint8_t task_cnt;
    uint8_t task_now;
    uint8_t menu_wtc;
    uint8_t dht11_buf[5];
    uint8_t mq135_buf[3];
    uint8_t mq2_buf[3];
    bool fire_past_state;
    bool fire_curr_state;
} TaskValueStruct;

extern TaskValueStruct TaskVST;

typedef struct Task_Threshold_Struct
{
    uint8_t temp_V;
    uint8_t humi_V;
    uint8_t air_V;
    uint8_t fume_V;
} TaskThresholdStruct;

extern TaskThresholdStruct TaskTST;

#ifndef JUDGE_IN_WHILE
void Task_Judge(uint32_t hb_timer);
#elif defined JUDGE_IN_WHILE
void Task_Judge(void);
#endif

void Task_Init(void);
void Task_System(void);
void T_DHT11_Read(void);
void T_MQ135AS_Read(void);
void T_MQ2FS_Read(void);
void T_FireSS_Read(void);
void T_Condition_Judge(void);
void T_Transmit_Data(void);
void T_Receive_Data(void);
void T_Memu_Switch(void);
void T_Key_Scan(void);

#endif