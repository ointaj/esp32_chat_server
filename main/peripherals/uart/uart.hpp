#pragma once

/**
 * @file   uart.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Uart basic initialization
 */

#include "output.hpp"
#include "uart_data.hpp"

/** @brief Initialzation of UART **/
class UART
{ 
    private:
        /** @brief Class tag **/
        static constexpr const char * m_TAG = "UART";

    protected:
        /** @brief Instance of UART config **/
        uart_config_t m_uart_config;
        /** @brief Instance of UART driver config **/
        s_uart_driver_conf_t m_uart_driver_conf;

    public:
        /**
         * @brief Constructor initializiint uart driver
         * @param uart_config      UART config
         * @param uart_driver_conf UART driver config
         * **/
        UART(const uart_config_t & uart_config,
             const s_uart_driver_conf_t & uart_driver_conf)
            : m_uart_config(uart_config),
              m_uart_driver_conf(uart_driver_conf)
        {
            // To avoid re-instalation same uart driver
            if (!uart_is_driver_installed(m_uart_driver_conf.m_uart_port_numb))
            {
                auto res = uart_param_config(m_uart_driver_conf.m_uart_port_numb,
                                             &m_uart_config);
                Output::esp_result_handler(e_abort_handle::et_THROW, res,
                                           m_TAG, "uart_param_config");
            
                res = uart_driver_install(m_uart_driver_conf.m_uart_port_numb,
                                          m_uart_driver_conf.m_rx_buffer_size,
                                          m_uart_driver_conf.m_tx_buffer_size,
                                          m_uart_driver_conf.m_queue_size,
                                          m_uart_driver_conf.m_uart_queue,
                                          m_uart_driver_conf.m_intr_alloc_flags);
                Output::esp_result_handler(e_abort_handle::et_THROW, res,
                                           m_TAG, "uart_driver_install");
            }
        }

        UART(const UART&) = delete;
        UART& operator=(const UART&) = delete;
        
        UART(UART &&) = delete;
        UART& operator=(UART&&) = delete;
};