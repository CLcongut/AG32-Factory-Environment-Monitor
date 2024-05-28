#include "main.h"

#define TAH_F_COLOR BLACK
#define TAH_B_COLOR WHITE
#define TAH_FONT 16
#define TEMP_X_POS 0
#define TEMP_Y_POS 0
#define HUMI_X_POS 0
#define HUMI_Y_POS 20

#define AIR_F_COLOR BLACK
#define AIR_B_COLOR WHITE
#define AIR_FONT 16
#define AIR_X_POS 0
#define AIR_Y_POS 40

#define FUME_F_COLOR BLACK
#define FUME_B_COLOR WHITE
#define FUME_FONT 16
#define FUME_X_POS 0
#define FUME_Y_POS 60

#define FIRE_F_COLOR BLACK
#define FIRE_B_COLOR WHITE
#define FIRE_FONT 16
#define FIRE_X_POS 0
#define FIRE_Y_POS 80

void Gui_Init(void)
{
    LCD_Init();
}

void Gui_Load(void)
{
    LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
}

void GUI_Show_TAH(void)
{
    float temp, humi;
    temp = TaskVST.dht11_buf[2] + TaskVST.dht11_buf[3] / 100.0;
    humi = TaskVST.dht11_buf[0] + TaskVST.dht11_buf[1] / 100.0;
    LCD_ShowFloatNum1(TEMP_X_POS, TEMP_Y_POS, temp, 4, TAH_F_COLOR, TAH_B_COLOR, TAH_FONT); // 温度
    LCD_ShowFloatNum1(HUMI_X_POS, HUMI_Y_POS, humi, 4, TAH_F_COLOR, TAH_B_COLOR, TAH_FONT); // 湿度
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

void GUI_Show_Fire(void)
{
    if (TaskVST.fire_state)
    {
        LCD_ShowString(FIRE_X_POS, FIRE_Y_POS, "is fire", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
    }
    else
    {
        LCD_ShowString(FIRE_X_POS, FIRE_Y_POS, "no fire", FIRE_F_COLOR, FIRE_B_COLOR, FIRE_FONT, 0);
    }
}