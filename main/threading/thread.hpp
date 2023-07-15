#pragma once

/**
 * @file   thread.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Thread spawning 
 */
/** @brief ESP-idf headers **/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/** @brief Standard headers**/
#include <assert.h>

/** @brief App headers **/
#include "thread_data.hpp"

/** @brief Represents type of task creation **/
enum class e_thread_creater : uint8_t
{
    /** @brief Basic creation of thread **/
    et_NO_AFFINITY,
    /** @brief Allow to create thread on specific core on CPU **/
    et_AFFINITY,
};

/**
 * @todo ADDED CUSTOM MOVE CONST AND DISABLE COPY CONST (ALSO OPERATORS)
 * **/

/** @brief Class represent working with threds in freeRTOS **/
class Thread final
{
    private:
        /** @brief Instance of thread config **/
        s_thread_config_t m_thread_config;
        /** @brief Handler fot thread **/
        TaskHandle_t m_thread_handler;
        /** @brief Type of creation thread **/
        e_thread_creater m_thread_creator_type;
        /** @brief True if thread was spawned **/
        bool thread_spawned;

    public:
        /** 
         * @brief Constructor for initializinng thread specification 
         * @param thread_function Function which will be runned in thread
         * @param thread_name Name of thread
         * @param thread_stack_size Size of thread stack
         * @param thread_priority Priority on which thread will be runned
         * @param thread_creator_type Type of creation for thread (specific core or basic)
         * @param spawn_thread True if thread should be spawned in constructor
         * @param core_number Number on which core should thread run in case of et_AFFINITY
         * **/
        Thread(std::function<void()> && thread_function,
               const char * thread_name,
               const uint32_t thread_stack_size,
               const UBaseType_t thread_priority,
               e_thread_creater thread_creator_type = e_thread_creater::et_NO_AFFINITY,
               bool spawn_thread = true,
               uint8_t core_number = 0)
            : m_thread_config{std::move(thread_function), thread_name,
                              thread_stack_size, thread_priority, core_number},
              m_thread_creator_type(thread_creator_type),
              thread_spawned(spawn_thread)
        {
            if (spawn_thread)
            {
                _spawn_thread();
            }
        }

    public:
        /** 
         * @brief Member function explicitly spawn and run thread
         * @return non 
         * **/
        inline void start()
        {
            // Thread cannot be spawned twice, cause abort()
            assert((!thread_spawned));
            _spawn_thread();
        }

    private:
        /**
         * @brief Member function which spawns (create) thread
         * @return non 
         * **/
        void _spawn_thread();
       
        /** 
         * @brief Member function called in thread and perfoming operationrs
         * @param ptr pointer to passed object in creator
         * @return non
         * **/
        static void _run(void * ptr)
        {
            // If nullptr cause abort()
            assert((nullptr != ptr));

            // Cast to param pass to task creator to Thread class
            Thread * thread = static_cast<Thread * >(ptr);

            // Performe thread function (infinite loop function)
            thread->_do();

            // Delete thread when performing has finished
            vTaskDelete(thread->m_thread_handler);
        }
    
    private:
        /**
         *  @brief Member function resposinble for performing thread function (infinite loop function) 
         *  @return non
         * **/
        inline void _do()
        {
            m_thread_config.m_thread_function();
        }
};