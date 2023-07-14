#pragma once

/**
 * @file   thread_data.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Data definition for thread
 */

/** @brief Standart headers **/
#include <functional>

/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"

/** @brief  All needed variables for working with freeRTOS threads **/
struct s_thread_config_t
{
    /** @brief chread function which will be run in as infinite loop **/
    std::function<void()> m_thread_function;
    /** @brief Thread name **/
    const char * m_thread_name = nullptr;
    /** @brief Thread stack size **/
    uint32_t m_thread_stack_size = 0;
    /** @brief Thread priority **/
    UBaseType_t  m_thread_priority = static_cast<UBaseType_t>(0);
    /** @brief Number on which core will be thread running **/
    uint8_t m_thread_core_run = 0;
};