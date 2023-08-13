#pragma once

/**
 * @file   event.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Event module of esp-idf custom events
 */

/** @brief App headers **/
#include "output.hpp"
#include "event_data.hpp"

/** @brief Createning own custom event type **/
ESP_EVENT_DECLARE_BASE(CUSTOM_EVENTS);

/** @brief All ID's of custom evetns**/
enum e_custom_event_id : int32_t
{
    et_INVALID_EVENT_ID,
    /** There you have to added new event id for custom event **/
    /**-------------------------------------------------------**/
    et_COUNT_CUSTOM_EVINTS
};

/** @brief Class represents creation and working with custom event **/
class CustomEvent final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "CustomEvent";
        /** @brief Flag is true when custom event has been deleted **/
        bool already_cleaned;

    private:
        /** @brief Event id of current event **/
        s_event_handler_conf_t m_event_handler_conf;
        /** @brief Event id of current event **/
        esp_event_loop_handle_t m_event_custom_loop;
        /** @brief Event id of current event **/
        esp_event_loop_args_t m_event_loop_args;

    public:
        /**
         * @brief Custom constructror initializing custom event
         * @param event_loop_args Arguments needed for custom event
         * **/
        CustomEvent(esp_event_loop_args_t const& event_loop_args)
            : already_cleaned(false),
              m_event_loop_args(event_loop_args)
        {
            Output::esp_result_handler(e_abort_handle::et_THROW,
                                       esp_event_loop_create(&m_event_loop_args, &m_event_custom_loop),
                                       m_TAG, "esp_event_loop_create");
        }

        /**
         * @brief Custom destructor cleaning up custom event
         * **/
        ~CustomEvent()
        {
            if (!already_cleaned)
            {
                clean_up();
            }
        }

        /**
         * @brief Deleted move/copy contructors
         * **/
        CustomEvent(CustomEvent const&) = delete;
        CustomEvent(CustomEvent &&) = delete;

        /**
         * @brief Deleted move/copy assigments operator
         * **/
        CustomEvent& operator=(CustomEvent const&) = delete;
        CustomEvent& operator=(CustomEvent &&) = delete;
    
    public:
        /**
         * @brief Registering handler for occurennce of event
         * @param event_hand_conf All needed conf data for event handler
         * @return non
         * **/
        void register_handler(s_event_handler_conf_t const& event_hand_conf);

        /**
         * @brief Posts event
         * @param event_data Data to be posted to the event handler
         * @param event_data_size Size of posted data
         * @param ticks_to_wait Maximum ticks the function should wait if the event queue is full. 
         * @return non
         * **/
        inline void post_event(const void * event_data,
                               const std::size_t event_data_size,
                               const TickType_t ticks_to_wait)
        {
            Output::esp_result_handler(e_abort_handle::et_NOT_THROW,
                                       esp_event_post_to(m_event_custom_loop,
                                                         m_event_handler_conf.m_event_type,
                                                         m_event_handler_conf.m_event_id, event_data,
                                                         event_data_size, ticks_to_wait),
                                       m_TAG, "esp_event_post_to");
        }

        /**
         * @brief Unregistering current handler
         * @return non
         * **/
        inline void unregister_handler()        
        {
            Output::esp_result_handler(e_abort_handle::et_THROW,
                                       esp_event_handler_instance_unregister_with(m_event_custom_loop,
                                                                                  m_event_handler_conf.m_event_type,
                                                                                  m_event_handler_conf.m_event_id,
                                                                                  m_event_handler_conf.m_instance),
                                       m_TAG, "esp_event_handler_instance_register_with");
        }
        /**
         * @brief Perfoming clean-up (unregistering handler and deleting loop)
         * @return non
         * **/
        inline void clean_up()
        {
            if (!already_cleaned)
            {
                already_cleaned = true;
                unregister_handler();
                Output::esp_result_handler(e_abort_handle::et_THROW,
                                           esp_event_loop_delete(m_event_custom_loop),
                                           m_TAG, "esp_event_loop_delete");
            }
        }
};
