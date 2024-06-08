#include "main.h"
#include "task.h"

uint16_t test_value1;
uint16_t test_value2;
uint16_t test_value3;

TaskValueStruct TaskVST;
TaskThresholdStruct TaskTST;

TaskPollingStruct TaskPST[] = {
    {true, 1000, false, T_DHT11_Read},
    {true, 1000, false, T_MQ135AS_Read},
    {true, 1000, false, T_MQ2FS_Read},
    {true, 1000, false, T_FireSS_Read},
    {false, 500, false, T_Memu_Switch},
    {false, 500, false, T_Condition_Judge},
    {false, 2000, false, T_Transmit_Data},
    {true, 500, false, T_Receive_Data}};

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
    if (!dht11_Read(TaskVST.dht11_buf))
    {
        GUI_Show_TAH();
    }
}

void T_MQ135AS_Read(void)
{
    if (MQ135AS_Read(TaskVST.mq135_buf))
    {
        GUI_Show_Air();
    }
}

void T_MQ2FS_Read(void)
{
    if (MQ2FS_Read(TaskVST.mq2_buf))
    {
        GUI_Show_Fume();
    }
}

void T_FireSS_Read(void)
{
    TaskVST.fire_curr_state = FireSS_Read();
    if (TaskVST.fire_curr_state != TaskVST.fire_past_state)
    {
        TaskVST.fire_past_state = TaskVST.fire_curr_state;
        GUI_Show_Fire(TaskVST.fire_curr_state);
    }
}

void T_Condition_Judge(void)
{
    if (TaskVST.mq2_buf[0] > TaskTST.fume_V ||
        TaskVST.mq135_buf[0] > TaskTST.air_V ||
        TaskVST.fire_curr_state == true)
    {
        Beep_ON();
    }
    else
    {
        Beep_OFF();
    }
}

void T_Transmit_Data(void)
{
    S_USART_Trans();
}

void T_Receive_Data(void)
{
    S_USART_Recev();
}

void T_Memu_Switch(void)
{
    switch (TaskVST.menu_wtc)
    {
    case 1:
        TaskPST[0].Task_Enable_Flag = true;
        TaskPST[1].Task_Enable_Flag = true;
        TaskPST[2].Task_Enable_Flag = true;
        TaskPST[3].Task_Enable_Flag = true;
        Gui_Load();
        break;

    case 2:
        TaskPST[0].Task_Enable_Flag = false;
        TaskPST[1].Task_Enable_Flag = false;
        TaskPST[2].Task_Enable_Flag = false;
        TaskPST[3].Task_Enable_Flag = false;
        Gui_Menu_2();
        break;

    case 3:
        TaskPST[0].Task_Enable_Flag = false;
        TaskPST[1].Task_Enable_Flag = false;
        TaskPST[2].Task_Enable_Flag = false;
        TaskPST[3].Task_Enable_Flag = false;
        Gui_Menu_3();
        break;
    }
    TaskPST[4].Task_Enable_Flag = false;
}