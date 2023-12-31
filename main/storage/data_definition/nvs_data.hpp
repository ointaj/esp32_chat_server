#pragma once

/**
 * @file   nvs_data.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Definitions of all structs needed for NVS operations
 */


/** @brief ESP-IDF headers **/
#include "nvs_flash.h"
#include "nvs.h"

/** @brief Struct represents configuration needed for NVS operations **/
struct s_nvs_config_t
{
    /** @brief NVS namespacen name **/
    const char * m_nvs_namespace_name;
    /** @brief NVS open mode **/
    nvs_open_mode_t m_nvs_mode;
    /** @brief Handle of nvs operation **/
    nvs_handle_t m_nvs_handle;
    /** @brief Result of nvs operation **/
    esp_err_t m_nvs_operation_res;
};
