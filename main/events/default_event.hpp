#pragma once

/**
 * @file   event.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Event module of esp-idf default events
 */

/** @brief App headers **/
#include "output.hpp"
#include "event_data.hpp"

/** @brief Class represents basic API for esp-idf default events (Singleton pattern) **/
class DefaultEvent final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "DefaultEvent";

    private:
        /**
         * @brief Custom constructor for initializing default event
         * **/
        DefaultEvent()
        {
             Output::esp_result_handler(e_abort_handle::et_THROW, esp_event_loop_create_default(),
                                        m_TAG, "esp_event_loop_create_default");
        }
    
    public:
        /**
         * @brief Getter for instance of DefaultEvent
         * @return referecnce to instance
         * **/
        inline static DefaultEvent & get_instance()
        {
            static DefaultEvent instance;
            return instance;
        }
        
        /**
         * @brief Registering handler for occurennce of event
         * @return non
         * **/
        inline void register_handler(s_event_handler_conf_t const& event_hand_conf)
        {
            Output::esp_result_handler(e_abort_handle::et_THROW,
                                       esp_event_handler_instance_register(event_hand_conf.m_event_type,
                                                                           event_hand_conf.m_event_id,
                                                                           event_hand_conf.m_event_handler,
                                                                           event_hand_conf.m_event_handler_arg,
                                                                           event_hand_conf.m_instance),
                                       m_TAG, "esp_event_handler_instance_register");
        }
};