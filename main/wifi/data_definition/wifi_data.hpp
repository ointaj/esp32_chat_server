#pragma once

/**
 * @file   wifi_data.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Data defintion of wifi values
 */

/** @brief Standart headers **/
#include "freertos/event_groups.h"
#include <array>


/** @brief Struct represents WiFi credentials for connection **/
struct s_wifi_credentials_t
{
    /** @brief SSID for AP **/
    std::array<char, 50> m_ssid;
    /** @brief Password for AP **/
    std::array<char, 50> m_password;
};

/** @brief Struct represents WiFi event data **/
struct s_wifi_event_data_t
{
    /** @brief Event group for signaling connection **/
    EventGroupHandle_t m_wifi_event_handle;
    /** @brief Count of connetetion attemps **/
    uint8_t m_connection_attempt_try = 0;
    /** @brief Event flag for forced dissconetion (if true, disconnetion was intetional) **/
    bool m_disconection_forced = false;
};