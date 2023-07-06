#pragma once

/**
 * @file   nvs_operation_handle.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  NVS storage functionality
 */


/** @brief Standard headers**/
#include <type_traits>
#include <string>
#include <string_view>

/** @brief App headers **/
#include "output.hpp"
#include "data_defintion/nvs_data.hpp"


/** @brief Macro defintion of checking nvs last operation, before executing new one **/
#define CHECK_NVS_OPERATION(RESULT_VAR) \
    if (ESP_OK != (RESULT_VAR)) { \
        return (RESULT_VAR); \
    }


/** @brief Class represent working with NVS storage **/
class NVSOperationHandle final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "NVS Operation Handle";

        /** @brief Instance of nvs config data **/
        s_nvs_config_t m_nvs_config;

    private:
        NVSOperationHandle(const char * nvs_namespace_name,
                           nvs_open_mode_t nvs_mode)
        {
            m_nvs_config.m_nvs_mode = nvs_mode;
            m_nvs_config.m_nvs_namespace_name = nvs_namespace_name;

            m_nvs_config.m_nvs_operation_res = nvs_open(m_nvs_config.m_nvs_namespace_name, nvs_mode,
                                                       &m_nvs_config.m_nvs_handle);
            Output::esp_result_handler(e_AbortHandle::NotThrow, m_nvs_config.m_nvs_operation_res, m_TAG, "nvs_open");
        }
    
    public:
        static NVSOperationHandle create(const char * nvs_namespace_name,
                                         nvs_open_mode_t nvs_mode)
        {
            return NVSOperationHandle(nvs_namespace_name, nvs_mode);
        }

        NVSOperationHandle(NVSOperationHandle const&) = delete;
        NVSOperationHandle& operator=(NVSOperationHandle const&) = delete;

        NVSOperationHandle(NVSOperationHandle &&) = default;
        NVSOperationHandle& operator=(NVSOperationHandle &&) = default;
       
        ~NVSOperationHandle()
        {
             // Check whenever is commit needed - write operation
            if (NVS_READWRITE == m_nvs_config.m_nvs_mode)
            {
                // Commit written changes to NVS flash
                m_nvs_config.m_nvs_operation_res = nvs_commit(m_nvs_config.m_nvs_handle);
                Output::esp_result_handler(e_AbortHandle::NotThrow, m_nvs_config.m_nvs_operation_res,
                                           m_TAG, "nvs_commit");
            }
            // Close handler
            nvs_close(m_nvs_config.m_nvs_handle);
        }

    public:
        template<typename T>
        esp_err_t write_to_nvs_storage_numb(const char * key, T value)
        {
            // We cannnot continue when previous operation (initialization in this case) has failed
            CHECK_NVS_OPERATION(m_nvs_config.m_nvs_operation_res);
            
            // When we passed empty key, m_nvs_namespace_name will be used as key
            static constexpr const char * l_key = _set_key(key, m_nvs_config.m_nvs_namespace_name);

            if constexpr (std::is_same_v<std::decay_t<T>, uint8_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_u8(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, uint16_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_u16(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, uint32_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_u32(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, uint64_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_u64(m_nvs_config.m_nvs_handle, l_key , value);
            }       
            else if constexpr (std::is_same_v<std::decay_t<T>, int8_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_i8(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, int16_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_i16(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, int32_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_i32(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, int64_t>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_i64(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else
            {
              static_assert(std::disjunction<std::is_same<std::decay_t<T>, uint8_t>,
                                             std::is_same<std::decay_t<T>, uint16_t>,
                                             std::is_same<std::decay_t<T>, uint32_t>,
                                             std::is_same<std::decay_t<T>, uint64_t>,
                                             std::is_same<std::decay_t<T>, int8_t>,
                                             std::is_same<std::decay_t<T>, int16_t>,
                                             std::is_same<std::decay_t<T>, int32_t>,
                                             std::is_same<std::decay_t<T>, int64_t>>::value,
                                             "Invalid type for write_to_nvs_storage_num");
            }

            Output::esp_result_handler(e_AbortHandle::NotThrow, m_nvs_config.m_nvs_operation_res, m_TAG, "write_to_nvs_storage_numb");

            return m_nvs_config.m_nvs_operation_res;
        }

        template<typename T>
        esp_err_t write_to_nvs_storage_str(const char * key, T value)
        {
            // We cannnot continue when previous operation (initialization in this case) has failed
            CHECK_NVS_OPERATION(m_nvs_config.m_nvs_operation_res);
            
            // When we passed empty key, m_nvs_namespace_name will be used as key
            // In this scenario l_key cannot be compute during compile-time, due to m_nvs_config.m_nvs_namespace_name
            const char * l_key = _set_key(key, m_nvs_config.m_nvs_namespace_name);

            if constexpr (std::is_same_v<std::decay_t<T>, std::string> ||
                          std::is_same_v<std::decay_t<T>, std::string_view>)
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_str(m_nvs_config.m_nvs_handle, l_key , value.data());
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, const char *> ||
                               std::is_same_v<std::decay_t<T>, char *>) 
            {
                m_nvs_config.m_nvs_operation_res = nvs_set_str(m_nvs_config.m_nvs_handle, l_key , value);
            }
            else
            {
                static_assert(std::disjunction<std::is_same<std::decay_t<T>, std::string>,
                                               std::is_same<std::decay_t<T>, std::string_view>,
                                               std::is_same<std::decay_t<T>, const char*>,
                                               std::is_same<std::decay_t<T>, char*>>::value,
                                               "Invalid type for write_to_nvs_storage_str");
            }

            Output::esp_result_handler(e_AbortHandle::NotThrow, m_nvs_config.m_nvs_operation_res, m_TAG, "write_to_nvs_storage_str");

            return m_nvs_config.m_nvs_operation_res;
        }

        template<typename T>
        esp_err_t write_to_nvs_storage_blob(const char * key, T * value)
        {

            // We cannnot continue when previous operation (initialization in this case) has failed
            CHECK_NVS_OPERATION(m_nvs_config.m_nvs_operation_res);
            
            if (nullptr != value)
            {
                // When we passed empty key, m_nvs_namespace_name will be used as key
                // In this scenario l_key cannot be compute during compile-time, due to m_nvs_config.m_nvs_namespace_name
                const char * l_key = _set_key(key, m_nvs_config.m_nvs_namespace_name);

                if constexpr (std::is_same_v<std::decay_t<T>, s_wifi_credentiols_t>)
                {
                    m_nvs_config.m_nvs_operation_res = nvs_set_blob(m_nvs_config.m_nvs_handle, l_key , value, sizeof(*value));
                }
                else
                {
                    static_assert(std::is_same_v<std::decay_t<T>, s_wifi_credentiols_t>, "Invalid type for write_to_nvs_storage_blob");
                }

                Output::esp_result_handler(e_AbortHandle::NotThrow, m_nvs_config.m_nvs_operation_res, m_TAG, "write_to_nvs_storage_blob");
            }

            return m_nvs_config.m_nvs_operation_res;
        }


    
    private:
        inline static constexpr const char * _set_key(const char * key,
                                                      const char * default_key)
        {
            const char * l_key = key;
            if ((nullptr == l_key) || (l_key[0] == '\0'))
            {
                l_key = default_key;
            }

            return l_key;
        }

};