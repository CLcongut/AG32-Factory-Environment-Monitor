#include "SYS.h"
#include "TASK.h"


TaskPollingStruct TaskPST[] = {
    {false, 100, false, T_DHT11_Read}};

TaskValueStruct Task_VST;

void T_DHT11_Read(void)
{
    dht11_Read(Task_VST.dht11_buf);
}

void Task_Clear_HB(void)
{
    HeartBeat.G_HB_Timer = 0;
}