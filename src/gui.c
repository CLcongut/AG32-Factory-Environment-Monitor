#include "board.h"
#include "lcd.h"
#include "Task.h"

#define TAH_F_COLOR BLACK
#define TAH_B_COLOR WHITE
#define TAH_SIZE 16

#define TEMP_X_POS 0
#define TEMP_Y_POS 0

#define HUMI_X_POS 0
#define HUMI_Y_POS 20

void Gui_Init(void)
{
    LCD_ShowChar(TEMP_X_POS + 35, TEMP_Y_POS, '.', TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE, 0);
    LCD_ShowChar(HUMI_X_POS + 35, HUMI_Y_POS, '.', TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE, 0);
}

void GUI_Show_tah(void)
{
    LCD_ShowIntNum(TEMP_X_POS, TEMP_Y_POS, TaskVST.dht11_buf[2], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE);      // 温度整数位
    LCD_ShowIntNum(TEMP_X_POS + 40, TEMP_Y_POS, TaskVST.dht11_buf[3], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE); // 温度小数位

    LCD_ShowIntNum(HUMI_X_POS, HUMI_Y_POS, TaskVST.dht11_buf[0], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE);      // 湿度整数位
    LCD_ShowIntNum(HUMI_X_POS + 40, HUMI_Y_POS, TaskVST.dht11_buf[1], 2, TAH_F_COLOR, TAH_B_COLOR, TAH_SIZE); // 湿度小数位
}