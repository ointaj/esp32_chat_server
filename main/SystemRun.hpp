#pragma once

/**
 * @brief Main logic of application
 * @copyright Oliver Sintaj 2023
 * **/


/** @brief Class represents main logic of application **/
class SystemRun final
{
    private:
        /** @brief instance of the class **/
        static SystemRun * _system_instance;

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
        /** @brief Main function that runs app **/
        void do_work(void);
};