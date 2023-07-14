#pragma once

/**
 * @file   thread_support.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Support for thread funcionality in freeRTOS 
 */

/** @brief App headers **/
#include "thread_values.hpp"

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