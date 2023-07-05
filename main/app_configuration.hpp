#pragma once

/**
 * @file   app_configuration.cpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed configuratuion for application
 */


/** @brief This macro allows all macro configuration for development mode **/
#define DEV_MODE

/** @brief This macro allows to be ESP_LOG* prints messages on the terminal **/
#ifdef DEV_MODE
    #define TERMINAL_OUTPUT
#endif // DEV_MODE