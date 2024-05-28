#include "board.h"
#include "main.h"

#include "task.h"
#include "gui.h"
#include "HB_GPTimer.h"

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
    Task_Init();
    Gui_Init();
    dht11_Init();
    FireSS_Init();

    Gui_Load();
    while (1)
    {
#ifdef JUDGE_IN_WHILE
        Task_Judge();
#endif
        Task_System();
    }
}