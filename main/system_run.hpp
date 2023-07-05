#pragma once

/**
 * @file   system_run.cpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Main file
 */


/** @brief Class represents main logic of application **/
class SystemRun final
{
    private:
        /** @brief Instance of the class **/
        static SystemRun * _system_instance;

        /** @brief Tag represents this module **/
        static constexpr const char * TAG = "SystemRun";

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
            if (nullptr == _system_instance)
            {
               _system_instance = new SystemRun();
            }

            return _system_instance;
        }

    public:
        /** @brief Main function that runs app 
         *  @return non**/
        void do_work(void);
};