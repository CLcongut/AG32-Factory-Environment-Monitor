#include "board.h"
#include "lcd.h"
#include "lcd_init.h"
#include "Task.h"

#define TAH_F_COLOR BLACK
#define TAH_B_COLOR WHITE
#define TAH_SIZE 16
#define TEMP_X_POS 0
#define TEMP_Y_POS 0
#define HUMI_X_POS 0
#define HUMI_Y_POS 20

#define AIR_F_COLOR BLACK
#define AIR_B_COLOR WHITE
#define AIR_SIZE 16
#define AIR_X_POS 0
#define AIR_Y_POS 40

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
    LCD_ShowFloatNum1(TEMP_X_POS, TEMP_Y_POS, temp, 4, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE); // 温度
    LCD_ShowFloatNum1(HUMI_X_POS, HUMI_Y_POS, humi, 4, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE); // 湿度
}

void GUI_Show_Air(void)
{
    float air;
    air = TaskVST.mq135_buf[0] + TaskVST.mq135_buf[1] / 100.0;
    LCD_ShowFloatNum1(AIR_X_POS, AIR_Y_POS, air, 4, AIR_F_COLOR, AIR_B_COLOR, AIR_SIZE);
}