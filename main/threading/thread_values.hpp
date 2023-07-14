#pragma once

/**
 * @file   thread_values.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Provide constant values for threading
 */

/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"

/** @brief Single OS tick in miliseconds **/
inline constexpr TickType_t SYSTEM_TICKS_MS = portTICK_PERIOD_MS;

/** @brief Maximal (infinite delay) **/
inline constexpr TickType_t INFINITE_WAIT = portMAX_DELAY;
