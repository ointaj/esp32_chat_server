#pragma once

/**
 * @file   wifi_values.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed values for Wifi module
 */

/** @brief Bit represents wifi station connectetion (device connected to some AP)**/
inline constexpr uint32_t WIFI_STA_CONNECTED = (1 << 0);

/** @brief Bit represents wifi station disconnectetion (device disconnected to some AP)**/
inline constexpr uint32_t WIFI_STA_DISCONNECTED = (1 << 1);

/** @brief Maximal count of re-try connetion of wifi **/
inline constexpr uint8_t WIFI_MAX_COUNT_OF_CONNETCTION_ATTEMPS = 10;