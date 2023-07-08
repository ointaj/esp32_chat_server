#pragma once

/**
 * @file   thread.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Support for thread funcionality in freeRTOS 
 */

/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"

/** @brief Single OS tick in miliseconds **/
inline constexpr TickType_t SYSTEM_TICKS_MS = portTICK_PERIOD_MS;

/** @brief Maximal (infinite delay) **/
inline constexpr TickType_t INFINITE_WAIT = portMAX_DELAY;

/** @brief Class represents thread support functionality **/
class TheadSupport final
{
    public:
        /**
         * @brief Calculate needed tick time for delays in lockers
         * @param ms Miliseconds we wan to wait
         * @return calculated delay
         * **/
        static inline constexpr TickType_t get_time_period(const TickType_t ms)
        {
            return (ms / SYSTEM_TICKS_MS);
        }
};