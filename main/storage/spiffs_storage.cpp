/** @brief App headers **/
#include "spiffs_storage.hpp"


esp_err_t SPIFFS::register_spiffs()
{
    esp_err_t ret = ESP_FAIL;
    // Check if spiffs is already mounted
    if (!esp_spiffs_mounted(m_spiffs_conf.partition_label))
    {
        // Register and mount SPIFFS to VFS
        ret = esp_vfs_spiffs_register(&m_spiffs_conf);
        Output::esp_result_handler(e_abort_handle::et_THROW, ret, m_TAG, "esp_vfs_spiffs_register");

        // Get all information about spiffs
        std::size_t file_system_size = 0, used_bytes = 0;
        ret = esp_spiffs_info(m_spiffs_conf.partition_label, &file_system_size, &used_bytes);

        // Check if esp_spiffs_info successed and print infou about spiffs
        if (!Output::esp_result_handler(e_abort_handle::et_NOT_THROW, ret, m_TAG,
                                        "esp_spiffs_info", "File system size : ", file_system_size,
                                        " Used bytes : ", used_bytes))
        {
            // We failed to get info about spiffs partion, try format to fix it
            ret = esp_spiffs_format(m_spiffs_conf.partition_label);
            Output::esp_result_handler(e_abort_handle::et_THROW, ret, m_TAG, "esp_spiffs_format");
        }

        if (used_bytes > file_system_size)
        {
            Output::log(e_log_type::et_WARN, m_TAG, "Number of used bytes cannot be larger than total");
            ret = check_consistacny_spiffs();
        }
    }

    return ret;
}

esp_err_t SPIFFS::check_consistacny_spiffs()
{
    esp_err_t ret = ESP_FAIL;

    Output::log(e_log_type::et_WARN, m_TAG, "Performing SPIFFS_check() This can take some time ...");
    ret = esp_spiffs_check(m_spiffs_conf.partition_label);
    if (!Output::esp_result_handler(e_abort_handle::et_NOT_THROW, ret, m_TAG, "esp_spiffs_format"))
    {
        // We failed to consistancy spiffs partion, try format to fix it
#ifdef M_D_FORMAT_NEW_PARTION_AFTER_CONSTANCY_FAILED
        Output::log(e_log_type::et_WARN, m_TAG,
                    "Performing SPIFFS_check() Failed, we are formating new partion, see M_D_FORMAT_NEW_PARTION_AFTER_CONSTANCY_FAILED...");
        ret = esp_spiffs_format(m_spiffs_conf.partition_label);
        Output::esp_result_handler(e_abort_handle::et_THROW, ret, m_TAG, "esp_spiffs_format");
#endif // M_D_FORMAT_NEW_PARTION_AFTER_CONSTANCY_FAILED
    }

    return ret;
}