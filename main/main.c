#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "can.h"
#include "diag.c"
#include "file_operations.h"

#include "oled.c"

volatile uint16_t timeSec = 0;
volatile uint8_t time10MSec = 0;
char config[2][4] = 
{
{1,29,1,1}, // 0
{ 2,2,2,2} // 1
};


void app_main()
{
    //setup RTC
    //setup SD card - for now it'll be stdout
    FILE * outfile = setup_fs();
    //setup CAN interface
    Oled_Init();
    CAN_Open();
    while (1) 
    {
        /*uint8_t exit = vwtp(config[0], outfile, false);
        printf("VWTP exited with %d\n", exit);*/
        Oled_PrintMG("25;0x025;0;0;",0);
        vTaskDelay(6000 / portTICK_PERIOD_MS);
    }
}
