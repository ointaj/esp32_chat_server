#pragma once

/**
 * @file   system_run.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Main file
 */

/** @brief App headers **/
#include "nvs_storage.hpp"


/** @brief Class represents main logic of application **/
class SystemRun final
{
    private:
        /** @brief Instance of the class **/
        static SystemRun * m_system_instance;

        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "SystemRun";

        /** @brief Instance of NVS Storage **/
        NVS m_nvs;

    private:
        /** @brief SystemRun constructor **/
        SystemRun() = default;

        /** @brief SystemRun copy-constructor deleted **/
        SystemRun(SystemRun const&) = delete;

        /** @brief SystemRun copy-assigment operator deleted **/
        SystemRun& operator=(SystemRun const&) = delete;

    public:
        /** 
         * @brief Get instance of class
         * @return instance of class 
         * **/
        static SystemRun * get_instance()
        {
            if (nullptr == m_system_instance)
            {
               m_system_instance = new SystemRun();
            }

            return m_system_instance;
        }

    public:
        /** @brief Main function that runs app 
         *  @return non**/
        void do_work(void);
};