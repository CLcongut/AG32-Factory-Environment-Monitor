#include "SYS.h"
#include "TASK.h"
#include "gui.h"

TaskValueStruct TaskVST;

TaskPollingStruct TaskPST[] = {
    {true, 100, false, T_DHT11_Read}};

void Task_Judge(void)
{
    for (uint8_t i = 0; i < TaskVST.task_cnt; i++)
    {
        if (TaskPST[i].Task_Enable_Flag)
        {
            if (!HeartBeat.G_HB_Timer % TaskPST[i].Task_Interval_Time)
            {
                TaskPST[i].Task_Status_Flag = 1;
            }
        }
    }
}

void Task_Init(void)
{
    TaskVST.task_now = 0;
    TaskVST.task_cnt = sizeof(TaskPST) / sizeof(TaskPST[0]);
}

void Task_System(void)
{
    if (TaskPST[TaskVST.task_now].Task_Status_Flag)
    {
        TaskPST[TaskVST.task_now].Function_Hook();
        TaskPST[TaskVST.task_now].Task_Status_Flag = 0;
    }
    if (++TaskVST.task_now >= TaskVST.task_cnt)
        TaskVST.task_now = 0;
}

void T_DHT11_Read(void)
{
    if (dht11_Read(TaskVST.dht11_buf))
    {
        GUI_Show_tah();
    }
}

void Task_Clear_HB(void)
{
    HeartBeat.G_HB_Timer = 0;
}