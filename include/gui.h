#ifndef GUI_H
#define GUI_H

void Gui_Init(void);
void Gui_Load(void);
void GUI_Show_Battery(void);
void GUI_Show_TAH(void);
void GUI_Show_Air(void);
void GUI_Show_Fume(void);
void GUI_Show_Fire(bool fireState);
void Gui_Menu_2(void);
void Gui_Menu_3(void);
void GUI_TS_Progress(uint8_t ts_wtc, uint8_t air_ts, uint8_t fume_ts);

#endif