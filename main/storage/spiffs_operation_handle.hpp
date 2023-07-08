#pragma once

/**
 * @file   spiffs_operation_handle.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  SPIFFS working with files using POSIX and C standard lib
 */


/** @brief Standard headers**/
#include <sys/unistd.h>
#include <sys/stat.h>
#include <string>
#include <string_view>

/** @brief App headers**/
#include "output.hpp"

class SPIFFSOperationHandle final
{
    public:
        /** @brief Reading mode **/
        static constexpr const char * READ_MODE = "r";
        /** @brief Writing mode **/
        static constexpr const char * WRITE_MODE = "w";
        /** @brief Append mode **/
        static constexpr const char * APPEND_MODE = "a";
    
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "SPIFFS Operation Handle";

        static constexpr std::string_view default_path = "/spiffs/";


        /** @brief File handler **/
        FILE * m_file_handler;

        /** @brief Current mode of working with file **/
        const char * m_current_mode;

        /** @brief File size in bytes **/
        std::size_t m_file_size;

    private:
        SPIFFSOperationHandle(std::string_view path_to_file,
                              const char * mode)
                : m_current_mode(mode), m_file_size(0)
        {
            const auto starts = _starts_with_default_path(path_to_file);
            const auto path = [starts, path_to_file]() -> std::string
            {
                if (!starts)
                {
                    return std::string(default_path) + std::string(path_to_file);
                }
                return std::string(path_to_file);
            }();
            // Open file
            m_file_handler = fopen(path.c_str(), mode);
            // Check if opening file was success
            if (is_file_open())
            {
              _get_file_info(path.c_str());
            }
        }
    
    private:
        inline bool _current_mode(const char * desired_mode)
        {
            bool res = true;
            if (m_current_mode != desired_mode)
            {
                res = false;
                Output::log(e_log_type::et_ERROR, m_TAG, "Current mode : ", m_current_mode,
                            " does not match witn operatation mode : ", desired_mode);
            }
            return res;
        }

        inline void _get_file_info(const char * path)
        {
            // Get relevant information about file 
            struct stat st;
            if (0 == stat(path, &st))
            {
                // Setting file size
                m_file_size = st.st_size;
            }
        }

        inline bool _starts_with_default_path(std::string_view path)
        {
            return path.substr(0, default_path.size()) == default_path;
        }
        

    public:
        /**
         * @brief Static "creator" of this class (factory pattern)
         * @param nvs_namespace_name Name of NVS namespace
         * @param nvs_mode           Open mode 
         * @return created object
         * **/
        static SPIFFSOperationHandle create(std::string_view path_to_file,
                                            const char * mode)
        {
            return SPIFFSOperationHandle(path_to_file, mode);
        }
        
        /** @brief Deleted copy constructor and operator **/
        SPIFFSOperationHandle(SPIFFSOperationHandle const&) = delete;
        SPIFFSOperationHandle& operator=(SPIFFSOperationHandle const&) = delete;

        /** @brief Default move constructor and operator declaration **/
        // this will be changed
        SPIFFSOperationHandle(SPIFFSOperationHandle &&) = default;
        SPIFFSOperationHandle& operator=(SPIFFSOperationHandle &&) = default;

        ~SPIFFSOperationHandle()
        {
            if (nullptr != m_file_handler)
            {
                fclose(m_file_handler);
            }
        }

    public:
        std::string read();

        bool write(std::string_view data);

        bool append(std::string_view data);

        bool seek();

        bool change_file_name(std::string_view filename);

        inline bool is_file_open()
        {
            bool res = true;
            if (nullptr != m_file_handler)
            {
                res = false;
                Output::log(e_log_type::et_ERROR, m_TAG, "File openning has failed !");
            }
            return res;
        }
};