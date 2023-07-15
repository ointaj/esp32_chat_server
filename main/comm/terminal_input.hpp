#pragma once

/**
 * @file   terminal_conf.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed configuratuion for terminal
 */

#include "uart.hpp"
#include "terminal_values.hpp"
#include "thread_values.hpp"

/** 
 * @brief  Default initialization of uart config for terminal readings
 * @return defaul uart config
 * **/
static constexpr uart_config_t __uart_default_config()
{
   return {
        .baud_rate = TERMINAL_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = TERMINAL_UART_THRESHOLD_RTS,
        .source_clk = UART_SCLK_APB
    };
}

/** 
 * @brief  Default initialization of uart driver config for terminal readings
 * @return defaul uart driver config
 * **/
static constexpr s_uart_driver_conf_t __uart_driver_default_config()
{
   return {
        .m_rx_buffer_size = TERMINAL_RX_BUFF_SIZE,
        .m_tx_buffer_size = TERMINAL_TX_BUFF_SIZE,
        .m_queue_size = TERMINAL_QUEUE_SIZE,
        .m_intr_alloc_flags = TERMINAL_INTR_ALLOC_FLAG,
        .m_uart_queue = nullptr,
        .m_uart_port_numb = TERMINAL_UART_PORT,
    };
}

/** @brief **/
class Terminal final : public UART
{   
    public:
        Terminal(const uart_config_t & uart_config,
                 const s_uart_driver_conf_t & uart_driver_conf)
            : UART(uart_config, uart_driver_conf)
        {}

    public:
        static inline Terminal create_default()
        {
            static constexpr auto uart_conf = __uart_default_config();
            static constexpr auto uart_driver_conf = __uart_driver_default_config();
            return Terminal(uart_conf, uart_driver_conf);
        }

        inline std::string read_line_blocking()
        {
            return read_line_blocking(INFINITE_WAIT);
        }

        std::string read_line_blocking(const TickType_t tick_to_wait);
    public:
        Terminal(const Terminal&) = delete;
        Terminal& operator=(const Terminal&) = delete;
        
        Terminal(Terminal &&) = delete;
        Terminal& operator=(Terminal&&) = delete;
};