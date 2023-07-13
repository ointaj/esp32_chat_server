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
#include "storage_locker.hpp"

/** @brief Class represents working with spiffs file sysstem
 *  @note  Thread-safe **/
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

        /** @brief Default path standars prefix 
         * 
         * @note All paths should be pass to this class like this -> /spiffs/file.txt
         * **/
        static constexpr std::string_view m_default_path = "/spiffs/";

        /** @brief Locker for SPIFFS filesystem **/
        Locker<StorageLocker> m_locker;

        /** @brief File handler **/
        FILE * m_file_handler;

        /** @brief Path to file **/
        std::string m_file_name;

        /** @brief Current mode of working with file **/
        const char * m_current_mode;

        /** @brief File size in bytes **/
        std::size_t m_file_size;

    private:
        /**
         * @brief Constructor initilizing all neeede members and perform open
         * @param path_to_file Path to file
         * @param mode Mode in which file is opened
         * **/
        SPIFFSOperationHandle(std::string && path_to_file,
                              const char * mode)
                : m_locker(StorageLocker::get_instance(et_SPIFFS).get_lock()),
                  m_file_name(std::move(path_to_file)),
                  m_current_mode(mode), m_file_size(0)
        {
            // Check if path is correct
            if (!_starts_with_default_path(m_file_name))
            {
                m_file_name = std::string(m_default_path) + m_file_name;
            }
            // Open file
            m_file_handler = fopen(m_file_name.c_str(), mode);
            // Check if opening file was success
            if (is_file_open())
            {
              _get_file_info(m_file_name.c_str());
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
            return path.substr(0, m_default_path.size()) == m_default_path;
        }
        

    public:
        /**
         * @brief Static "creator" of this class (factory pattern)
         * @param nvs_namespace_name Name of NVS namespace
         * @param nvs_mode           Open mode 
         * @return created object
         * **/
        static SPIFFSOperationHandle create(std::string && path_to_file,
                                            const char * mode)
        {
            return SPIFFSOperationHandle(std::move(path_to_file), mode);
        }
        
        /** @brief Deleted copy constructor and operator **/
        SPIFFSOperationHandle(SPIFFSOperationHandle const&) = delete;
        SPIFFSOperationHandle& operator=(SPIFFSOperationHandle const&) = delete;

        /** @brief Custom move constructor and setting other SPIFFSOperationHandle as default **/
        SPIFFSOperationHandle(SPIFFSOperationHandle && other)
                : m_locker(std::move(other.m_locker)),
                  m_file_handler(other.m_file_handler),
                  m_file_name(std::move(m_file_name)),
                  m_current_mode(other.m_current_mode),
                  m_file_size(other.m_file_size)
        {
            // Setting other to default
            other.m_file_handler = nullptr;
            other.m_current_mode = nullptr;
            other.m_file_size = 0;
        }

        /** @brief Custom move assigment operator and setting other SPIFFSOperationHandle as default **/
        SPIFFSOperationHandle& operator=(SPIFFSOperationHandle && other)
        {
            if (this != &other)
            {
                m_locker = std::move(other.m_locker);
                m_file_handler = other.m_file_handler;
                m_file_name = std::move(other.m_file_name);
                m_current_mode = other.m_current_mode;
                m_file_size = other.m_file_size;
                // Setting other to default
                other.m_file_handler = nullptr;
                other.m_current_mode = nullptr;
                other.m_file_size = 0;
            }

            return *this;
        }

        /** @brief Destructor which calls close on file **/
        ~SPIFFSOperationHandle()
        {
            if (nullptr != m_file_handler)
            {
                fclose(m_file_handler);
            }
        }

    public:
        /**
         * @brief Reads data from the file
         * @return returns filled string with data in file
         * **/
        std::string read();

        /**
         * @brief Writes data to the file
         * @param data Data to be written 
         * @return true if write was successful
         * **/
        bool write(std::string_view data);

        /**
         * @brief Appends data to the file
         * @param data Data to be written 
         * @return true if write was successful
         * **/
        bool append(std::string_view data);
 
        /**
         * @brief Performe seek in file
         * @param position position (offset) 
         * @return true if write was successful
         * **/
        bool seek(int64_t position,
                  int32_t whence);
        
        /**
         * @brief Remove file
         * @return true if removing was succesful
         * **/
        bool remove();

        /**
         * @brief Change name of file
         * @param new_filename name of file
         * @return true if renaming was succesful
         * **/
        bool change_file_name(std::string && new_filename);

        /**
         * @brief Check if file is open
         * @return true when file is open
         * **/
        inline bool is_file_open()
        {
            bool res = false;
            if (nullptr != m_file_handler)
            {
                res = true;
            }
            return res;
        }
};