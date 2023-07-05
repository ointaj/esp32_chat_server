#pragma once

/**
 * @file   nvs_storage.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  NVS storage functionality
 */


/** @brief ESP-IDF headers **/
#include "nvs_flash.h"

/** @brief App headers **/
#include "output.hpp"


/** @brief Class represent work with NVS storage **/
class NVS final
{
    private:
        static constexpr const char * m_TAG = "NVS Storage";

    public:
        NVS()
        {
            auto res = nvs_flash_init();
            if (res == ESP_ERR_NVS_NO_FREE_PAGES || res == ESP_ERR_NVS_NEW_VERSION_FOUND)
            {
                res = nvs_flash_erase();
                Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_erase");
                res = nvs_flash_init();
                Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_init");
            }
            Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_init");
        }

};
