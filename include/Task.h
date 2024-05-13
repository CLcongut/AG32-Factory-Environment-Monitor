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
    uint8_t *dht11_buf;
} TaskValueStruct;

extern TaskValueStruct Task_VST;

void T_DHT11_Read(void);

#endif