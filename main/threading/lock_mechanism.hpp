#pragma once

/**
 * @file   lock_mechanizm.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  RAII pattern for locking freeRTOS mutex
 */


/** @brief Standart headers **/
#include <type_traits>


/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "assert.h"

/** @brief Forward declarations of all lockers in the system**/
class StorageLocker;

/** @brief Class represents RAII pattern for locking and un-locking mutexes **/
template <typename T,
          typename = std::enable_if_t<std::is_same_v<T, StorageLocker>>>
class Locker final
{
    private:
        /** @brief Reference to a locker (mutex) **/
        T * m_locker;

        /** @brief Miliseconds how much time should xSemaphoreTake wait if mutex its not available **/
        TickType_t m_lock_time;
        
        /** @brief Flag is true when a semaphore is locked **/
        bool m_is_locked;

    public:
        /**
         * @brief Constructor thats initilize reference to mutex and can lock
         * @param locker Reference to a locker object
         * @param ms     Miliseconds how much time should xSemaphoreTake wait if mutex its not available
         * @param lock   If flag is true, locking is perfomed in constructor
         * **/
        Locker(T * locker,
               const TickType_t ms,
               const bool lock)
            : m_locker(locker),
              m_lock_time(ms),
              m_is_locked(lock)
        {

            assert((locker != nullptr));
            // Check if we should lock in constructor
            if (lock)
            {
                // Setting flag, trui if xSemaphoreTake successed (mutex was locked)
                m_is_locked = xSemaphoreTake(m_locker->m_mutex, m_lock_time);
            }
        }

        /**
         * @brief Trying perfome locking of mutex
         * @return result of locking
         * **/
        inline bool try_lock()
        {
            // Cannot lock if is already locked
            assert(!m_is_locked);
            
            // Perfoming locking
            m_is_locked = xSemaphoreTake(m_locker->m_mutex, m_lock_time);

            return m_is_locked;
        }
        
        /**
         * @brief Checking if mutex is locked
         * @return flag for locking
         * **/
        inline bool is_locked()
        {
            return m_is_locked;
        }

        ~Locker()
        {
            // Releasing semaphore is only possible when locking was sucessful
            if (m_is_locked)
            {
                xSemaphoreGive(m_locker->m_mutex);
            }
        }

        /** @brief Deleted copy constructor/operator **/
        Locker(Locker const&) = delete;
        Locker& operator=(Locker const&) = delete;

        /** @brief Move constructor, which will set other Locker to default state**/
        Locker(Locker && other) : m_locker(other.m_locker),
                                  m_lock_time(other.m_lock_time),
                                  m_is_locked(other.m_is_locked)
        {
            other.m_locker = nullptr;
        }

        /** @brief Move assigment operator, which will set other Locker to default state**/
        Locker& operator=(Locker && other)
        {
            if (this != &other)
            {
                m_locker = other.m_locker;
                m_lock_time = other.m_lock_time;
                m_is_locked = other.m_is_locked;
                other.m_locker = nullptr;
            }

            return *this;
        }
};