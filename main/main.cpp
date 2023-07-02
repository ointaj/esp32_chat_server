#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <tuple>
#include "esp_log.h"

#include "wifi.hpp"

extern "C"
{
    /** @brief  Main funciton which run process one 
     *  @param  non 
     *  @return non **/
    void app_main(void);
}

/** @see app_main(void) **/
void app_main(void)
{
    while (1)
    {
        vTaskDelay(100);
        ESP_LOGI("APP", "Waiting....");
    }
}
