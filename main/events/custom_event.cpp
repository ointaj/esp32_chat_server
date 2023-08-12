#include "custom_event.hpp"

void CustomEvent::register_handler(s_event_handler_conf_t const& event_hand_conf)
 {
    if (event_hand_conf.m_event_type != CUSTOM_EVENTS)
    {
        Output::log(e_log_type::et_ERROR, m_TAG, "Cannot register custom event with other event type (base) as CUSTOM_EVENTS");
        return;
    }
    if ((event_hand_conf.m_event_id >= et_COUNT_CUSTOM_EVINTS)
         && (event_hand_conf.m_event_id <= et_INVALID_EVENT_ID))
    {
        Output::log(e_log_type::et_ERROR, m_TAG, "Cannot register custom event with un-existing ID - see e_custom_event_id");
        return;
    }

    m_event_handler_conf = event_hand_conf;
    Output::esp_result_handler(e_abort_handle::et_THROW,
                               esp_event_handler_instance_register_with(m_event_custom_loop,
                                                                        event_hand_conf.m_event_type,
                                                                        event_hand_conf.m_event_id,
                                                                        event_hand_conf.m_event_handler,
                                                                        event_hand_conf.m_event_handler_arg,
                                                                        event_hand_conf.m_instance),
                               m_TAG, "esp_event_handler_instance_register_with");
}