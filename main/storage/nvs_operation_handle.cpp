/** @brief App headers **/
#include "nvs_operation_handle.hpp"

/** see header **/
esp_err_t NVSOperationHandle::read_nvs_storage_str(const char * key,
                                                   std::string & value)
{
    esp_err_t res = ESP_FAIL;

    // Check if operatrion can be perfomre, based on mode
    M_CHECK_OPERATION_TYPE(m_nvs_config.m_nvs_mode, e_nvs_operation_type::et_READ, m_TAG);

    // We cannnot continue when previous operation (initialization in this case) has failed
    M_CHECK_NVS_OPERATION(m_nvs_config.m_nvs_operation_res);
      
    // When we passed empty key, m_nvs_namespace_name will be used as key
    const char * l_key = _set_key(key);

    std::size_t neeeded_size = 0;
    res = nvs_get_str(m_nvs_config.m_nvs_handle, l_key , nullptr, &neeeded_size);
    
    if (Output::esp_result_handler(e_abort_handle::et_NOT_THROW, res, m_TAG, "read_nvs_storage_str - getting size"))
    {
        value.resize(neeeded_size);
        res = nvs_get_str(m_nvs_config.m_nvs_handle, l_key , value.data(), &neeeded_size);
    }

    Output::esp_result_handler(e_abort_handle::et_NOT_THROW, res, m_TAG, "read_nvs_storage_str - read");

    return res;
}                                                   