#include "main.h"
#include "task.h"

uint16_t test_value1;
uint16_t test_value2;
uint16_t test_value3;

TaskValueStruct TaskVST;

TaskPollingStruct TaskPST[] = {
    {true, 1000, false, T_DHT11_Read},
    {true, 500, false, T_MQ135AS_Read},
    {true, 500, false, T_MQ2FS_Read}};

#ifndef JUDGE_IN_WHILE
void Task_Judge(uint32_t hb_timer)
{
    for (uint8_t i = 0; i < TaskVST.task_cnt; i++)
    {
        if (TaskPST[i].Task_Enable_Flag)
        {
            if ((hb_timer % TaskPST[i].Task_Interval_Time) == 0)
            {
                TaskPST[i].Task_Status_Flag = 1;
            }
        }
    }
}
#elif defined JUDGE_IN_WHILE
void Task_Judge(void)
{
    for (uint8_t i = 0; i < TaskVST.task_cnt; i++)
    {
        if (TaskPST[i].Task_Enable_Flag)
        {
            if ((HeartBeat.HB_Timer % TaskPST[i].Task_Interval_Time) == 0)
            {
                TaskPST[i].Task_Status_Flag = 1;
            }
        }
    }
}
#endif

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
    // if (!dht11_Read(TaskVST.dht11_buf))
    // {
    //     GUI_Show_TAH();
    // }
    LCD_ShowIntNum(0, 0, test_value1++, 4, BLACK, WHITE, 16);
}

void T_MQ135AS_Read(void)
{
    // if (MQ135AS_Read(TaskVST.mq135_buf))
    // {
    //     GUI_Show_Air();
    // }
    LCD_ShowIntNum(0, 20, test_value2++, 4, BLACK, WHITE, 16);
}

void T_MQ2FS_Read(void)
{
    LCD_ShowIntNum(0, 40, test_value3++, 4, BLACK, WHITE, 16);
}