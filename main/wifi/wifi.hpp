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
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sys.h"

/** @brief App headers **/
#include "output.hpp"
#include "default_event.hpp"
#include "wifi_data.hpp"

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

        /** @brief Event data **/
        s_wifi_event_data_t m_wifi_event_data;

        /** @brief WiFi init configuration **/
        wifi_init_config_t m_cfg = WIFI_INIT_CONFIG_DEFAULT();

        /** @brief WiFi configuration for STA and AP**/
        wifi_config_t m_wifi_config;

    public:
        WifiModule()
        {
            m_wifi_event_data.m_wifi_event_handle = xEventGroupCreate();
            // Init TCP/IP stack
            Output::esp_result_handler(e_abort_handle::et_THROW, esp_netif_init(),
                                       m_TAG, " esp_netif_init");
            
            // Creates default event loop
            auto & default_event = DefaultEvent::get_instance();

            // Creates default wifi for STA and AP
            esp_netif_create_default_wifi_sta();
            esp_netif_create_default_wifi_ap();

            // Register event handler for wifi event
            default_event.register_handler(_get_wifi_event_handler_conf());

            Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_init(&m_cfg),
                                       m_TAG, " esp_netif_init");
        }
    
    public:
        /**
         * @brief 
         * @param
         * @return 
         * **/
        void start_wifi(s_wifi_credentials_t const& wifi_credentials);

        /**
         * @brief 
         * @param
         * @return 
         * **/
        void stop_sta_mode();

    private:
        /**
         * @brief 
         * @return 
         * **/
        inline s_event_handler_conf_t _get_wifi_event_handler_conf()
        {
            return {
                .m_event_type = WIFI_EVENT,
                .m_event_id = ESP_EVENT_ANY_ID,
                .m_event_handler = &_wifi_event_handler,
                .m_event_handler_arg = &m_wifi_event_data,
                .m_instance = nullptr
            };
        }
        
        /**
         * @brief 
         * @param
         * @param
         * @param
         * @param
         * @return 
         * **/
        static void _wifi_event_handler(void* arg,
                                        esp_event_base_t event_base,
                                        int32_t event_id,
                                        void* event_data);

};