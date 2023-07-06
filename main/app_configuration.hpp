#pragma once

/**
 * @file   app_configuration.cpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed configuratuion for application
 */


/** @brief This macro allows all macro configuration for development mode **/
#define M_D_DEV_MODE

/** @brief This macro allows to be ESP_LOG* prints messages on the terminal **/
#ifdef M_D_DEV_MODE
    #define M_D_TERMINAL_OUTPUT
#endif // DEV_MODE