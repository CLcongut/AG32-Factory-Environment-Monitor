#include "board.h"
#include "main.h"

#include "usart.h"
#include "task.h"
#include "gui.h"
#include "HB_GPTimer.h"

#include "lcd.h"
#include "lcd_init.h"
#include "DHT11.h"
#include "mq135_air_sensor.h"
#include "mq2_fumes_sensor.h"
#include "fire_sensor.h"

#include "beep.h"
#include "relay.h"
#include "step_motor.h"

int main(void)
{
    board_init();
    GpTimer0_Heart_Init(1000, 100);
    S_USART_Init();
    Task_Init();
    Gui_Init();
    dht11_Init();
    FireSS_Init();
    Beep_Init();

    Gui_Load();
    while (1)
    {
#ifdef JUDGE_IN_WHILE
        Task_Judge();
#endif
        Task_System();
    }
}