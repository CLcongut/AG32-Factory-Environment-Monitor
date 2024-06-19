#include "board.h"
#include "main.h"

#include "usart.h"
#include "task.h"
#include "gui.h"
#include "HB_GPTimer.h"
#include "key.h"
#include "route.h"

#include "lcd.h"
#include "lcd_init.h"
#include "DHT11.h"
#include "mq135_air_sensor.h"
#include "mq2_fumes_sensor.h"
#include "fire_sensor.h"

int main(void)
{
    board_init();
    GpTimer0_Heart_Init(1000, 100);
    S_USART_Init();
    Key_Init();
    Gui_Init();
    dht11_Init();
    FireSS_Init();
    Device_Init();

    Task_Init();
    Gui_Load();
    // Gui_Menu_2();
    // Gui_Menu_3();
    TaskVST.menu_wtc = 1;
    while (1)
    {
#ifdef JUDGE_IN_WHILE
        Task_Judge();
#endif
        Task_System();
    }
}