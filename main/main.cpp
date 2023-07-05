/** @brief ESP-IDF headers **/
#include "esp_system.h"

/** @brief App headers **/
#include "system_run.hpp"

extern "C"
{
    /** @brief  Main funciton which run as "process one" 
     *  @return non **/
    void app_main(void);
}

/** @see app_main(void) **/
void app_main(void)
{
    SystemRun::get_instance()->do_work();
}
