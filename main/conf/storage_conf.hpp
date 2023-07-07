#pragma once

/** @brief App headers **/
#include "app_conf.hpp"

/**
 * @file   storage_conf.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed configuratuion for storage
 */

/** @brief This macro allows to run SPIFFS chcek on system start **/
#ifdef M_D_DEV_MODE
    // #define M_D_SPIFFS_CHECK_ON_START
#endif // DEV_MODE

/** @brief This macro allows to run SPIFFS formating new parttion if constiscky check failed 
 * 
 *  @note  If you allow this configurain, you are aware of lossing old data on partition
 * **/
#define M_D_FORMAT_NEW_PARTION_AFTER_CONSTANCY_FAILED