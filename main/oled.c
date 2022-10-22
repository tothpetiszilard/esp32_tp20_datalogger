#include "oled.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"
#include "font8x8_basic.h"

static 	SSD1306_t dev;
static TaskHandle_t CyclicTaskHdl = NULL;

static char screenBuff[15];

static void Oled_Cyclic(void *pvParameters);

void Oled_Init()
{
#if CONFIG_I2C_INTERFACE
	//ESP_LOGI(tag, "INTERFACE is i2c");
	//ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	//ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	//ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	//ESP_LOGI(tag, "INTERFACE is SPI");
	//ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	//ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	//ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	//ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	//ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	//ESP_LOGW(tag, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	//ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	//ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

    xTaskCreate(Oled_Cyclic, "Oled", 2048, NULL, 4, &CyclicTaskHdl);
}

void Oled_Print(char * str)
{
    char * buffPtr;
    buffPtr = screenBuff;
    while ((*str != 0) && (buffPtr <= &screenBuff[14]))
    {
        *buffPtr++ = *str++;
    }
}

static void Oled_Cyclic(void *pvParameters)
{
    while(1)
    {
        ssd1306_clear_screen(&dev, false);
        ssd1306_contrast(&dev, 0xff);
        //ssd1306_display_text_x3(&dev, 0, "Hello", 5, false);
        ssd1306_display_text(&dev, 0, &screenBuff[0], sizeof(screenBuff), false);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    
}
