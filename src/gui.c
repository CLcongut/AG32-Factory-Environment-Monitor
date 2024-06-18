#include "main.h"

#define RoundedCorners
#define RC_COLOR GRAY

#define BAT_F_COLOR BLACK
#define BAT_B_COLOR WHITE
#define BAT_FONT 12
#define BAT_X_POS 4
#define BAT_Y_POS 4

#define BEEP_F_COLOR BLACK
#define BEEP_B_COLOR WHITE
#define BEEP_FONT 12
#define BEEP_X_POS 110
#define BEEP_Y_POS 4

#define TAH_F_COLOR WHITE
#define TAH_B_COLOR GRAY
#define TAH_FONT 16
#define TEMP_X_POS 42
#define TEMP_Y_POS 24
#define HUMI_X_POS 42
#define HUMI_Y_POS 46

#define AIR_F_COLOR WHITE
#define AIR_B_COLOR GRAY
#define AIR_FONT 16
#define AIR_X_POS 42
#define AIR_Y_POS 72

#define FUME_F_COLOR WHITE
#define FUME_B_COLOR GRAY
#define FUME_FONT 16
#define FUME_X_POS 42
#define FUME_Y_POS 94

#define FIRE_F_COLOR WHITE
#define FIRE_B_COLOR GRAY
#define FIRE_FONT 16
#define FIRE_X_POS 86
#define FIRE_Y_POS 24

#define TAG_F_COLOR BLACK
#define TAG_B_COLOR WHITE
#define TAG_FONT 12
#define TAG_X_POS 12
#define TAG_Y_POS 140

void Gui_Init(void)
{
    LCD_Init();
}

void Gui_Load(void)
{
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    LCD_ShowChinese(BAT_X_POS, BAT_Y_POS, "BT", BAT_F_COLOR, BAT_B_COLOR, 16, 0);         // 显示电量图标
    LCD_ShowIntNum(BAT_X_POS + 18, BAT_Y_POS, 90, 2, BAT_F_COLOR, BAT_B_COLOR, BAT_FONT); // 暂用占位
    LCD_ShowChar(BAT_X_POS + 32, BAT_Y_POS, '%', BAT_F_COLOR, BAT_B_COLOR, BAT_FONT, 0);  // 显示电量百分比

    LCD_ShowChinese(BEEP_X_POS - 42, BEEP_Y_POS, "蜂鸣器", BEEP_F_COLOR, BEEP_B_COLOR, BEEP_FONT, 0);
    LCD_ShowChar(BEEP_X_POS - 6, BEEP_Y_POS, ':', BEEP_F_COLOR, BEEP_B_COLOR, BEEP_FONT, 0);
    LCD_ShowChinese(BEEP_X_POS, BEEP_Y_POS, "开", BEEP_F_COLOR, BEEP_B_COLOR, BEEP_FONT, 0);

    LCD_ShowChinese(TEMP_X_POS - 38, TEMP_Y_POS, "温度", TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0); // 显示温度标识
    LCD_ShowChar(TEMP_X_POS - 7, TEMP_Y_POS, ':', TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0);        // 显示温度标识
    LCD_ShowChinese(TEMP_X_POS + 16, TEMP_Y_POS, "DG", TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0);   // 显示摄氏度

    LCD_ShowChinese(HUMI_X_POS - 38, HUMI_Y_POS, "湿度", TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0); // 显示温度标识
    LCD_ShowChar(HUMI_X_POS - 7, HUMI_Y_POS, ':', TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0);        // 显示温度标识
    LCD_ShowChinese(HUMI_X_POS + 16, HUMI_Y_POS, "PC", TAH_F_COLOR, TAH_B_COLOR, TAH_FONT, 0);   // 显示摄氏度

    LCD_ShowChinese(AIR_X_POS - 38, AIR_Y_POS, "空气", AIR_F_COLOR, AIR_B_COLOR, AIR_FONT, 0);
    LCD_ShowChar(AIR_X_POS - 7, AIR_Y_POS, ':', AIR_F_COLOR, AIR_B_COLOR, AIR_FONT, 0);
    LCD_ShowChinese(AIR_X_POS + 40, AIR_Y_POS, "PC", AIR_F_COLOR, AIR_B_COLOR, AIR_FONT, 0);

    LCD_ShowChinese(FUME_X_POS - 38, FUME_Y_POS, "烟雾", FUME_F_COLOR, FUME_B_COLOR, FUME_FONT, 0);
    LCD_ShowChar(FUME_X_POS - 7, FUME_Y_POS, ':', FUME_F_COLOR, FUME_B_COLOR, FUME_FONT, 0);
    LCD_ShowChinese(FUME_X_POS + 40, FUME_Y_POS, "PC", FUME_F_COLOR, FUME_B_COLOR, FUME_FONT, 0);

    LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS, "当前", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
    LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS + 22, "无火", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);

    LCD_ShowChinese(TAG_X_POS, TAG_Y_POS, "菜单", TAG_F_COLOR, TAG_B_COLOR, TAG_FONT, 0);
    LCD_ShowChinese(TAG_X_POS + 33, TAG_Y_POS, "确认", TAG_F_COLOR, TAG_B_COLOR, TAG_FONT, 0);
    LCD_ShowChinese(128 - TAG_X_POS - 37, TAG_Y_POS, "正", TAG_F_COLOR, TAG_B_COLOR, TAG_FONT, 0);
    LCD_ShowChinese(128 - TAG_X_POS - 12, TAG_Y_POS, "负", TAG_F_COLOR, TAG_B_COLOR, TAG_FONT, 0);

#ifdef RoundedCorners
    LCD_DrawLine(TEMP_X_POS - 37, TEMP_Y_POS - 1, TEMP_X_POS + 31, TEMP_Y_POS - 1, RC_COLOR);
    LCD_DrawLine(TEMP_X_POS - 37, TEMP_Y_POS + 16, TEMP_X_POS + 31, TEMP_Y_POS + 16, RC_COLOR);
    LCD_DrawLine(TEMP_X_POS - 39, TEMP_Y_POS + 1, TEMP_X_POS - 39, TEMP_Y_POS + 15, RC_COLOR);
    LCD_DrawLine(TEMP_X_POS + 32, TEMP_Y_POS + 1, TEMP_X_POS + 32, TEMP_Y_POS + 15, RC_COLOR);

    LCD_DrawLine(HUMI_X_POS - 37, HUMI_Y_POS - 1, HUMI_X_POS + 31, HUMI_Y_POS - 1, RC_COLOR);
    LCD_DrawLine(HUMI_X_POS - 37, HUMI_Y_POS + 16, HUMI_X_POS + 31, HUMI_Y_POS + 16, RC_COLOR);
    LCD_DrawLine(HUMI_X_POS - 39, HUMI_Y_POS + 1, HUMI_X_POS - 39, HUMI_Y_POS + 15, RC_COLOR);
    LCD_DrawLine(HUMI_X_POS + 32, HUMI_Y_POS + 1, HUMI_X_POS + 32, HUMI_Y_POS + 15, RC_COLOR);

    LCD_DrawLine(AIR_X_POS - 37, AIR_Y_POS - 1, AIR_X_POS + 55, AIR_Y_POS - 1, RC_COLOR);
    LCD_DrawLine(AIR_X_POS - 37, AIR_Y_POS + 16, AIR_X_POS + 55, AIR_Y_POS + 16, RC_COLOR);
    LCD_DrawLine(AIR_X_POS - 39, AIR_Y_POS + 1, AIR_X_POS - 39, AIR_Y_POS + 15, RC_COLOR);
    LCD_DrawLine(AIR_X_POS + 56, AIR_Y_POS + 1, AIR_X_POS + 56, AIR_Y_POS + 15, RC_COLOR);

    LCD_DrawLine(FUME_X_POS - 37, FUME_Y_POS - 1, FUME_X_POS + 55, FUME_Y_POS - 1, RC_COLOR);
    LCD_DrawLine(FUME_X_POS - 37, FUME_Y_POS + 16, FUME_X_POS + 55, FUME_Y_POS + 16, RC_COLOR);
    LCD_DrawLine(FUME_X_POS - 39, FUME_Y_POS + 1, FUME_X_POS - 39, FUME_Y_POS + 15, RC_COLOR);
    LCD_DrawLine(FUME_X_POS + 56, FUME_Y_POS + 1, FUME_X_POS + 56, FUME_Y_POS + 15, RC_COLOR);

    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 16, FIRE_X_POS + 32, FIRE_Y_POS + 16, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 17, FIRE_X_POS + 32, FIRE_Y_POS + 17, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 18, FIRE_X_POS + 32, FIRE_Y_POS + 18, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 19, FIRE_X_POS + 32, FIRE_Y_POS + 19, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 20, FIRE_X_POS + 32, FIRE_Y_POS + 20, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS, FIRE_Y_POS + 21, FIRE_X_POS + 32, FIRE_Y_POS + 21, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS + 1, FIRE_Y_POS - 1, FIRE_X_POS + 31, FIRE_Y_POS - 1, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS + 1, FIRE_Y_POS + 38, FIRE_X_POS + 31, FIRE_Y_POS + 38, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS - 1, FIRE_Y_POS + 1, FIRE_X_POS - 1, FIRE_Y_POS + 37, RC_COLOR);
    LCD_DrawLine(FIRE_X_POS + 32, FIRE_Y_POS + 1, FIRE_X_POS + 32, FIRE_Y_POS + 37, RC_COLOR);

#endif
}

void GUI_Show_Battery(void)
{
}

void GUI_Show_TAH(void)
{
    LCD_ShowIntNum(TEMP_X_POS, TEMP_Y_POS, TaskVST.dht11_buf[2], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_FONT);
    LCD_ShowIntNum(HUMI_X_POS, HUMI_Y_POS, TaskVST.dht11_buf[0], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_FONT);
}

void GUI_Show_Air(void)
{
    float air;
    air = TaskVST.mq135_buf[0] + TaskVST.mq135_buf[1] / 100.0;
    LCD_ShowFloatNum1(AIR_X_POS, AIR_Y_POS, air, 4, AIR_F_COLOR, AIR_B_COLOR, AIR_FONT);
}

void GUI_Show_Fume(void)
{
    float fume;
    fume = TaskVST.mq2_buf[0] + TaskVST.mq2_buf[1] / 100.0;
    LCD_ShowFloatNum1(FUME_X_POS, FUME_Y_POS, fume, 4, FUME_F_COLOR, FUME_B_COLOR, FUME_FONT);
}

void GUI_Show_Fire(bool fireState)
{
    if (fireState)
    {
        LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS, "发现", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
        LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS + 22, "火源", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
    }
    else
    {
        LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS, "当前", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
        LCD_ShowChinese(FIRE_X_POS, FIRE_Y_POS + 22, "无火", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
    }
}

#define AIR_TS_X_POS 58
#define AIR_TS_Y_POS 138

#define FUME_TS_X_POS 98
#define FUME_TS_Y_POS 138
void Gui_Menu_2(void)
{
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    LCD_ShowChinese(4, 4, "阈", BLACK, WHITE, 16, 0);
    LCD_ShowChinese(4, 22, "值", BLACK, WHITE, 16, 0);
    LCD_ShowChinese(4, 40, "设", BLACK, WHITE, 16, 0);
    LCD_ShowChinese(4, 58, "定", BLACK, WHITE, 16, 0);
    LCD_DrawRectangle(AIR_TS_X_POS - 2, AIR_TS_Y_POS + 2, AIR_TS_X_POS + 11, AIR_TS_Y_POS - 100, BLACK);
    LCD_ShowChinese(AIR_TS_X_POS - 10, AIR_TS_Y_POS + 4, "空气", BLACK, WHITE, 16, 0);

    LCD_DrawRectangle(FUME_TS_X_POS - 2, FUME_TS_Y_POS + 2, FUME_TS_X_POS + 11, FUME_TS_Y_POS - 100, BLACK);
    LCD_ShowChinese(FUME_TS_X_POS - 10, FUME_TS_Y_POS + 4, "烟雾", BLACK, WHITE, 16, 0);
    GUI_TS_Progress(0, TaskTST.air_V, TaskTST.fume_V);
    LCD_DrawLine(AIR_TS_X_POS, AIR_TS_Y_POS, AIR_TS_X_POS + 10, AIR_TS_Y_POS, BLACK);
    LCD_DrawLine(FUME_TS_X_POS, FUME_TS_Y_POS, FUME_TS_X_POS + 10, FUME_TS_Y_POS, BLACK);
}

void GUI_TS_Progress(uint8_t ts_wtc, uint8_t air_ts, uint8_t fume_ts)
{
    if (ts_wtc == 1)
    {
        LCD_DrawLine(AIR_TS_X_POS, AIR_TS_Y_POS - air_ts, AIR_TS_X_POS + 10, AIR_TS_Y_POS - air_ts, WHITE);
        LCD_DrawLine(AIR_TS_X_POS, AIR_TS_Y_POS - air_ts + 1, AIR_TS_X_POS + 10, AIR_TS_Y_POS - air_ts + 1, BLACK);
        LCD_ShowIntNum(AIR_TS_X_POS, AIR_TS_Y_POS - 115, air_ts, 2, RED, WHITE, 12);
        LCD_ShowIntNum(FUME_TS_X_POS, FUME_TS_Y_POS - 115, fume_ts, 2, BLACK, WHITE, 12);
    }
    else if (ts_wtc == 2)
    {
        LCD_DrawLine(FUME_TS_X_POS, FUME_TS_Y_POS - fume_ts, FUME_TS_X_POS + 10, FUME_TS_Y_POS - fume_ts, WHITE);
        LCD_DrawLine(FUME_TS_X_POS, FUME_TS_Y_POS - fume_ts + 1, FUME_TS_X_POS + 10, FUME_TS_Y_POS - fume_ts + 1, BLACK);
        LCD_ShowIntNum(FUME_TS_X_POS, FUME_TS_Y_POS - 115, fume_ts, 2, RED, WHITE, 12);
        LCD_ShowIntNum(AIR_TS_X_POS, AIR_TS_Y_POS - 115, air_ts, 2, BLACK, WHITE, 12);
    }
    else
    {
        for (uint8_t i = 0; i < air_ts; i++)
        {
            LCD_DrawLine(AIR_TS_X_POS, AIR_TS_Y_POS - i, AIR_TS_X_POS + 10, AIR_TS_Y_POS - i, BLACK);
        }
        for (uint8_t i = 0; i < fume_ts; i++)
        {
            LCD_DrawLine(FUME_TS_X_POS, FUME_TS_Y_POS - i, FUME_TS_X_POS + 10, FUME_TS_Y_POS - i, BLACK);
        }
        LCD_ShowIntNum(FUME_TS_X_POS, FUME_TS_Y_POS - 115, fume_ts, 2, BLACK, WHITE, 12);
        LCD_ShowIntNum(AIR_TS_X_POS, AIR_TS_Y_POS - 115, air_ts, 2, BLACK, WHITE, 12);
    }
}

#define null

void Gui_Menu_3(void)
{
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
    LCD_ShowChinese(4, 2, "菜单菜单菜单菜单菜单", BLACK, WHITE, 12, 0);
}

void GUI_Route_Control(void)
{
}
