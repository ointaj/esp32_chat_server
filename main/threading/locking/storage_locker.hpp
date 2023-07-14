#pragma once

/**
 * @file   storage_locker.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Wrapper for freeRTOS mutex
 */

/** @brief App headers **/
#include "lock_mechanism.hpp"
#include "thread_values.hpp"

/** @brief Enum represents types of FS/Storages in the app **/
enum e_storage_locker_types : uint8_t
{
    et_NVS,
    et_SPIFFS,
    et_COUNT
};

/** @brief Class represents wrapper of freeRTOS mutex for storage access (NVS, SPIFFS)**/
class StorageLocker final
{
    // To allow Locker access private member
    friend class Locker<StorageLocker>;

    private:
        /** @brief Mutex handle - holts mutex **/
        SemaphoreHandle_t m_mutex;

        /** @brief Flag that tells if init locker during construction (in constructor) **/
        static constexpr bool m_locker_lock_in_init = true;

    private:
        /** @brief Constructor initialize mutex **/
        StorageLocker()
        {
            // Creating of mutex
            m_mutex = xSemaphoreCreateMutex();
            assert(m_mutex != nullptr);
        }

        /** @brief Destructor deleting mutex **/
        ~StorageLocker()
        {
            // Delete semaphore
            vSemaphoreDelete(m_mutex);
        }
    
    public:
        /**
         * @brief Static member function returning reference to one of the storace locker (mutex)
         * @param locker_id id (or index) represents type of storage locker
         * @return reference to a locker (mutex) object
         * **/
        static StorageLocker & get_instance(const e_storage_locker_types locker_id)
        {
            assert(((et_COUNT > locker_id) || (et_NVS <= locker_id)));

            static StorageLocker lockers[et_COUNT];

            return lockers[locker_id];
        }
        
        /**
         * @brief Member function which creates lock
         * @return locked mutex
         * **/
        inline Locker<StorageLocker> get_lock()
        {
            return Locker<StorageLocker>(this, INFINITE_WAIT, m_locker_lock_in_init);
        }

        /** @brief Deleted copy constructor/operator **/
        StorageLocker(StorageLocker const&) = delete;
        StorageLocker& operator=(StorageLocker const&) = delete;

        /** @brief Deleted move constructor/operator **/
        StorageLocker(StorageLocker &&) = delete;
        StorageLocker& operator=(StorageLocker &&) = delete;

};
