#pragma once

/**
 * @file   event_data.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Data defintion of events values
 */

/** @brief ESP-IDF headers **/
#include "esp_event.h"

/** @brief Struct represents all neeeded data for registering esp event handler **/
struct s_event_handler_conf_t
{
    /** @brief Type of event (WiFi, Bluetooth, custom etc) **/
    esp_event_base_t m_event_type;
    /** @brief Id ov event type **/
    int32_t m_event_id;
    /** @brief Function which will be called **/
    esp_event_handler_t m_event_handler;
    /** @brief Data, aside from event data, that is passed to the handler when it is called **/
    void * m_event_handler_arg;
    /** @brief  Instance of specific handler (This needs to be kept if the specific callback instance should be unregistered before deleting the whole event loop)**/
    esp_event_handler_instance_t * m_instance;
};