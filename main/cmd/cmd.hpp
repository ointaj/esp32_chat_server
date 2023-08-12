#pragma once

/**
 * @file   cmd.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All commands
 */

/** @brief App headers s**/
#include "output.hpp"
#include "terminal_input.hpp"
#include "nvs_operation_handle.hpp"

class CMD final
{
    private:
        static constexpr const char * m_TAG = "CMD";

    
    public:
    
    public:
        esp_err_t set_wifi_credentials();
};