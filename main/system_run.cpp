/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/** @brief App headers **/
#include "system_run.hpp"
#include "output.hpp"
#include "storage_locker.hpp"

/** see header **/
void SystemRun::do_work()
{   
    while (1)
    {
        vTaskDelay(100);
        Output::log(e_log_type::et_WARN, m_TAG, "Hi ", 88);
    }
}
