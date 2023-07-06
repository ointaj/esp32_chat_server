/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/** @brief App headers **/
#include "system_run.hpp"
#include "output.hpp"


/** see header **/
SystemRun * SystemRun::m_system_instance = nullptr;

static constexpr const char * per = ";l";

/** see header **/
void SystemRun::do_work()
{
    while (1)
    {
        vTaskDelay(100);
        Output::log(e_log_type::et_WARN, m_TAG, "Hi ", 88);
    }
}
