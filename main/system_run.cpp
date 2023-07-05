
/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/** @brief App headers **/
#include "system_run.hpp"
#include "output.hpp"


/** see header **/
SystemRun * SystemRun::_system_instance = nullptr;

/** see header **/
void SystemRun::do_work()
{
    while (1)
    {
        vTaskDelay(100);
        Output::log(e_LogType::Warn, TAG, "Hi ", 88, 12552);
    }
}

