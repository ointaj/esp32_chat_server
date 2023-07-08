#pragma once

/**
 * @file   system_run.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Main file
 */

/** @brief App headers **/
#include "nvs_storage.hpp"
#include "spiffs_storage.hpp"
#include "nvs_operation_handle.hpp"
#include "spiffs_operation_handle.hpp"


/** @brief Class represents main logic of application **/
class SystemRun final
{
    private:
        /** @brief Instance of NVS Storage **/
        NVS m_nvs;

        /** @brief Instance of SPIFFS file system **/
        SPIFFS m_spiffs;
        
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "SystemRun";

    private:
        /** @brief SystemRun constructor **/
        SystemRun() : m_spiffs(nullptr, nullptr, 5, true, true)
        {
        }

        /** @brief SystemRun copy-constructor deleted **/
        SystemRun(SystemRun const&) = delete;

        /** @brief SystemRun copy-assigment operator deleted **/
        SystemRun& operator=(SystemRun const&) = delete;

        /** @brief SystemRun move-constructor deleted **/
        SystemRun(SystemRun &&) = delete;

        /** @brief SystemRun move-assigment operator deleted **/
        SystemRun& operator=(SystemRun &&) = delete;

    public:
        /** 
         * @brief Get instance of class
         * @return instance of class 
         * **/
        static SystemRun & get_instance()
        {
            static SystemRun system_run;
            return system_run;
        }

    public:
        /** @brief Main function that runs app 
         *  @return non**/
        void do_work(void);
};