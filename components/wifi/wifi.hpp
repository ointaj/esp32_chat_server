#pragma once

/** @brief ESP-IDF headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
/** @brief App headers **/
#include "output.hpp"

/**
 * @file   wifi.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Full WiFi configuration and communication
 */

/** @brief Class represend all functionialty needed for WiFi **/
class WifiModule final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "WiFi Module";

        static EventGroupHandle_t m_wifi_event_handle;

        wifi_config_t wifi_config;
    
    public:
        WifiModule()
        {
            m_wifi_event_handle =  xEventGroupCreate();

            Output::esp_result_handler(e_AbortHandle::Throw, esp_netif_init(),
                                       m_TAG, " esp_netif_init");
            Output::esp_result_handler(e_AbortHandle::Throw, esp_event_loop_create_default(),
                                       m_TAG, " esp_event_loop_create_default");
            wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
            Output::esp_result_handler(e_AbortHandle::Throw, esp_wifi_init(),
                                       m_TAG, " esp_netif_init");

        }
};