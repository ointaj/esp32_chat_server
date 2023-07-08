#pragma once

/**
 * @file   spiffs_storage.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  SPIFFS file system functionality
 */

/** @brief ESP-IDF headers **/
#include "esp_spiffs.h"

/** @brief App headers **/
#include "output.hpp"
#include "storage_conf.hpp"

/** @brief Class represent initialization of SPIFFS file system **/
class SPIFFS final
{
    private:
        /** @brief Tag represents this module **/
        static constexpr const char * m_TAG = "SPIFFS File System";

        /** @brief Default path for spiffs **/
        static constexpr const char * m_default_path = "/spiffs";

        /** @brief Main configurattion of SPIFFS file system **/
        esp_vfs_spiffs_conf_t m_spiffs_conf;


    public:

        /**
         * @brief Constructor for initializaton of SPIFFS file system
         * @param path                   Default path where SPIFFS will be mounted, if nullptr, then default is set
         * @param partion_label          Partion lable for SPIFFS, if nullptr then subtype from partitions.csv will be used
         * @param max_open_file          Maximal count of open files at same time
         * @param format_if_mount_failed If true, it will format the file system if it fails to mount
         * @param mount                  If trie, it will mount FS during initialization of object
         * **/
        SPIFFS(const char * path,
               const char * partiton_label,
               const std::size_t max_open_file,
               const bool format_if_mount_failed,
               const bool mount)
            : m_spiffs_conf{((path == nullptr) ? m_default_path : path),
                             partiton_label, max_open_file, format_if_mount_failed}
        {
        // Check FS consistancy
#ifdef M_D_SPIFFS_CHECK_ON_START
        Output::esp_result_handler(e_abort_handle::et_THROW, check_consistacny_spiffs(),
                                   m_TAGm " check_consistacny_spiffs");
#endif //M_D_SPIFFS_CHECK_ON_START

            // TODO - add ther chcek, if some time passed and we need to run esp_spiffs_check() - at first we need to have NTP

            // Check if we want to mount in initiazation of this class
            if (mount)
            {
                // Mount FS
                register_spiffs();
            }
        }

    public:
        /**
         * @brief Mount (register) file system 
         * @return result of mouting
         * **/
        esp_err_t register_spiffs();

        /**
         * @brief Constistancy check of file system
         * @return result of check
         * **/
        esp_err_t check_consistacny_spiffs();
};