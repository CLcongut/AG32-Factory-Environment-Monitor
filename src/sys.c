#include "board.h"

#include "SYS.h"
#include "TASK.h"
#include "gui.h"

#include "HB_GPTimer.h"

#include "DHT11.h"

void _sys_Init(void)
{
    Task_Init();
    Gui_Init();
}

void _sys_Load(void)
{
}

void _sys_Loop(void)
{
}