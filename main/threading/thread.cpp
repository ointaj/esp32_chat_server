#include "thread.hpp"


/** see header**/
void Thread::_spawn_thread()
{
    switch (m_thread_creator_type)
    {
        case e_thread_creater::et_AFFINITY:
        {
            const auto res = xTaskCreatePinnedToCore(&Thread::_run,
                                    m_thread_config.m_thread_name,
                                    m_thread_config.m_thread_stack_size,
                                    this,
                                    m_thread_config.m_thread_priority,
                                    &m_thread_handler,
                                    static_cast<BaseType_t>(m_thread_config.m_thread_core_run));
            assert((res == pdPASS));
            break;
        }
        case e_thread_creater::et_NO_AFFINITY:
        {
            const auto res = xTaskCreate(&Thread::_run,
                        m_thread_config.m_thread_name,
                        m_thread_config.m_thread_stack_size,
                        this,
                        m_thread_config.m_thread_priority,
                        &m_thread_handler);
            assert((res == pdPASS));
            break;
        }
        default:
        {
            assert(false);
            break;
        }   
    }
}