#include "wifi.hpp"
#include "wifi_values.hpp"

/** see header **/
void WifiModule::_wifi_event_handler(void * arg,
                                     esp_event_base_t event_base,
                                     int32_t event_id,
                                     void * event_data)
{
    switch (event_id)
    {
        case WIFI_EVENT_STA_START:
        {
            esp_wifi_connect();
            break;
        }
        case WIFI_EVENT_STA_CONNECTED:
        {
            s_wifi_event_data_t * data = static_cast<s_wifi_event_data_t*>(arg);
            xEventGroupSetBits(data->m_wifi_event_handle, WIFI_STA_CONNECTED);
            Output::log(e_log_type::et_INFO, m_TAG, "Connected to the AP successfuly");
            break;
        }
        case WIFI_EVENT_STA_DISCONNECTED:
        {
            s_wifi_event_data_t * data = static_cast<s_wifi_event_data_t*>(arg);
            if (data->m_disconection_forced)
            {
                xEventGroupSetBits(data->m_wifi_event_handle, WIFI_STA_DISCONNECTED);
                Output::log(e_log_type::et_WARN, m_TAG, "Disconnected from AP");
            }
            else if (data->m_connection_attempt_try < WIFI_MAX_COUNT_OF_CONNETCTION_ATTEMPS)
            {
                esp_wifi_connect();
                data->m_connection_attempt_try++;
                Output::log(e_log_type::et_WARN, m_TAG, "Retrying connection...");
            }
            else
            {
                data->m_connection_attempt_try = 0;
                xEventGroupSetBits(data->m_wifi_event_handle, WIFI_STA_DISCONNECTED);
                Output::log(e_log_type::et_ERROR, m_TAG, "Connection has failed");
            }

            break;
        }
        case WIFI_EVENT_STA_STOP:
        case WIFI_EVENT_AP_STACONNECTED:
        case WIFI_EVENT_AP_STADISCONNECTED:
        default:
        {
            break;
        }
    }
}

/** see header **/
void WifiModule::start_wifi(s_wifi_credentials_t const& wifi_credentials)
{
    // Setting main WiFi configuration
    m_wifi_config = {
        .sta = {
            .ssid = wifi_credentials.m_ssid,
            .password = wifi_credentials.m_password,
        },
        .ap = {
            .ssid = WIFI_AP_SSID,
            .ssid_len = strlen(WIFI_AP_PASS),
            .password = WIFI_AP_PASS,
            .max_connection = WIFI_AP_MAX_CONNECTION,
            .authmode = WIFI_AP_AUTH_MODE
        }
    };

    Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_set_mode(WIFI_MODE_APSTA),
                               m_TAG, "esp_wifi_set_mode()");
    Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_set_config(WIFI_IF_STA, &m_wifi_config),
                               m_TAG, "esp_wifi_set_config(WIFI_IF_STA)");
    Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_set_config(WIFI_IF_AP, &m_wifi_config),
                               m_TAG, "esp_wifi_set_config(WIFI_IF_AP)");
    Output::esp_result_handler(e_abort_handle::et_THROW, esp_wifi_start(),
                               m_TAG, "esp_wifi_start()");
 
    EventBits_t bits = xEventGroupWaitBits(m_wifi_event_data.m_wifi_event_group,
            WIFI_STA_CONNECTED | WIFI_STA_DISCONNECTED,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);
    
    if (bits & WIFI_STA_CONNECTED)
    {

    }
    else if (bits & WIFI_STA_DISCONNECTED)
    {

    }
    else
    {
        
    }
} 