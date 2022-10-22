#ifndef OLED_H
#define OLED_H

#include "esp_types.h"

extern void Oled_Init();
extern void Oled_Print(char * str);
extern void Oled_PrintMG(char * str,uint8_t dataPos);

#endif //OLED_H