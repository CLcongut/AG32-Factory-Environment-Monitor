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
    {true, 100, false, T_Key_Scan},
    {false, 500, false, T_Condition_Judge},
    {false, 3000, false, T_Transmit_Data},
    {true, 500, false, T_Receive_Data},
};

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
                TaskPST[i].Task_Status_Flag = true;
            }
        }
    }
}
#endif

void Task_Init(void)
{
    TaskVST.task_now = 0;
    TaskVST.task_cnt = sizeof(TaskPST) / sizeof(TaskPST[0]);
    TaskTST.air_V = 1;
    TaskTST.fume_V = 1;
}

void Task_System(void)
{
    if (TaskPST[TaskVST.task_now].Task_Status_Flag)
    {
        TaskPST[TaskVST.task_now].Function_Hook();
        TaskPST[TaskVST.task_now].Task_Status_Flag = false;
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
    if (TaskVST.mq2_buf[0] > TaskTST.fume_V)
    {
        Output1_Route(1);
    }
    else
    {
        Output1_Route(0);
    }
    if (TaskVST.mq135_buf[0] > TaskTST.air_V)
    {
        Output2_Route(1);
    }
    else
    {
        Output2_Route(0);
    }
    if (TaskVST.fire_curr_state == true)
    {
        Output3_Route(1);
    }
    else
    {
        Output3_Route(0);
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
        TaskPST[0].Task_Status_Flag = false;
        TaskPST[1].Task_Status_Flag = false;
        TaskPST[2].Task_Status_Flag = false;
        Gui_Menu_2();
        break;

#ifdef MENU3ENABLE
    case 3:
        Gui_Menu_3();
        break;
#endif
    }
    TaskPST[4].Task_Enable_Flag = false;
}

void T_Key_Scan(void)
{
    uint8_t Key_Num = Key_Scan();
    if (TaskVST.menu_wtc == 1)
    {
        if (Key_Num == 1)
        {
            TaskVST.menu_wtc++;
            TaskPST[4].Task_Enable_Flag = true;
        }
        Key_Num = 0;
    }
    if (TaskVST.menu_wtc == 2)
    {
        switch (Key_Num)
        {
        case 1:
#ifndef MENU3ENABLE
            TaskVST.menu_wtc = 1;
#elif defined MENU3ENABLE
            TaskVST.menu_wtc++;
#endif
            TaskTST.ts_switch = 0;
            TaskPST[4].Task_Enable_Flag = true;
            TaskTST.ts_temp[0] = TaskTST.air_V;
            TaskTST.ts_temp[1] = TaskTST.fume_V;
            break;

        case 2:
            if (++TaskTST.ts_switch > 2)
                TaskTST.ts_switch = 1;
            GUI_TS_Progress(TaskTST.ts_switch, TaskTST.air_V, TaskTST.fume_V);
            break;

        case 3:
            if (TaskTST.ts_switch == 1)
            {
                if (++TaskTST.air_V > 99)
                {
                    TaskTST.air_V = 99;
                }
            }
            else if (TaskTST.ts_switch == 2)
            {
                if (++TaskTST.fume_V > 99)
                {
                    TaskTST.fume_V = 99;
                }
            }

            GUI_TS_Progress(TaskTST.ts_switch, TaskTST.air_V, TaskTST.fume_V);
            break;

        case 4:
            if (TaskTST.ts_switch == 1)
            {
                if (--TaskTST.air_V < 1)
                {
                    TaskTST.air_V = 1;
                }
            }
            else if (TaskTST.ts_switch == 2)
            {
                if (--TaskTST.fume_V < 1)
                {
                    TaskTST.fume_V = 1;
                }
            }
            GUI_TS_Progress(TaskTST.ts_switch, TaskTST.air_V, TaskTST.fume_V);
            break;

        case 13:
            if (TaskTST.ts_switch == 1)
            {
                if (++TaskTST.air_V > 99)
                {
                    TaskTST.air_V = 99;
                }
            }
            else if (TaskTST.ts_switch == 2)
            {
                if (++TaskTST.fume_V > 99)
                {
                    TaskTST.fume_V = 99;
                }
            }

            GUI_TS_Progress(TaskTST.ts_switch, TaskTST.air_V, TaskTST.fume_V);
            break;

        case 14:
            if (TaskTST.ts_switch == 1)
            {
                if (--TaskTST.air_V < 1)
                {
                    TaskTST.air_V = 1;
                }
            }
            else if (TaskTST.ts_switch == 2)
            {
                if (--TaskTST.fume_V < 1)
                {
                    TaskTST.fume_V = 1;
                }
            }
            GUI_TS_Progress(TaskTST.ts_switch, TaskTST.air_V, TaskTST.fume_V);
            break;
        }
        Key_Num = 0;
    }
#ifdef MENU3ENABLE
    if (TaskVST.menu_wtc == 3)
    {
        switch (Key_Num)
        {
        case 1:
            TaskVST.menu_wtc = 1;
            TaskPST[4].Task_Enable_Flag = true;
            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;
        }
        Key_Num = 0;
    }
#endif
    // LCD_ShowIntNum(0, 120, Key_Scan(), 2, BLACK, WHITE, 12);
}
