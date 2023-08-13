#include "wifi.hpp"
#include "wifi_values.hpp"

/** see header **/
void WifiModule::_wifi_event_handler(void* arg,
                                     esp_event_base_t event_base,
                                     int32_t event_id,
                                     void* event_data)
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
                Output::log(e_log_type::et_ERROR, m_TAG, "Retrying connection...");
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
        {
            break;
        }
        case WIFI_EVENT_AP_STACONNECTED:
        {
            break;
        }
        case WIFI_EVENT_AP_STADISCONNECTED:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}