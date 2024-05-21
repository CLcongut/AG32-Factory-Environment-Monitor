#ifndef TASK_H
#define TASK_H

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
    uint8_t dht11_buf[5];
} TaskValueStruct;

extern TaskValueStruct TaskVST;

void Task_Init(void);
void T_DHT11_Read(void);
void Task_Clear_HB(void);

#endif