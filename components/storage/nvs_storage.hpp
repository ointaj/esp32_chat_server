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
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "NVS Storage";

    public:
        NVS()
        {
            // Main initialization of NVS storage system
            auto res = nvs_flash_init();
            if ((res == ESP_ERR_NVS_NO_FREE_PAGES) || (res == ESP_ERR_NVS_NEW_VERSION_FOUND))
            {
                // Erasing of NVS storage system - needed in case of those errors
                res = nvs_flash_erase();
                Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_erase");
                // Re-initialization of NVS storage system - needed in case of those errors
                res = nvs_flash_init();
                Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_init");
            }
            Output::esp_result_handler(e_AbortHandle::Throw, res, m_TAG, "nvs_flash_init");
        }
};
