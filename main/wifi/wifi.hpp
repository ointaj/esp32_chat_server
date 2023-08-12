#pragma once

/**
 * @file   wifi.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Wifi module
 */

/** @brief ESP-IDF headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

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

/** @brief Class represents all functionialty needed for WiFi **/
class WifiModule final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "WiFi Module";

        /** @brief Event group for signaling connection **/
        static EventGroupHandle_t m_wifi_event_handle;

        /** @brief WiFi init configuration **/
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

        /** @brief WiFi configuration **/
        wifi_config_t wifi_config;
    
    public:
        WifiModule()
        {
            m_wifi_event_handle =  xEventGroupCreate();
            // Init TCP/IP stack
            Output::esp_result_handler(e_abort_handle::et_THROW, esp_netif_init(),
                                       m_TAG, " esp_netif_init");
            
            /** @todo maybe move esp_event to /main/events ? **/
            // Creates default event loop 
            Output::esp_result_handler(e_abort_handle::et_THROW, esp_event_loop_create_default(),
                                       m_TAG, " esp_event_loop_create_default");
            esp_netif_create_default_wifi_sta();
            esp_netif_create_default_wifi_ap();
            Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_init(&cfg),
                                       m_TAG, " esp_netif_init");
        }
};