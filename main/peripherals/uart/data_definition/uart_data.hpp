#pragma once

/**
 * @file   uart_data.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Uart data defintion
 */

#include "driver/uart.h"

/** @brief Data struct represenet all needed values for UART driver **/
struct s_uart_driver_conf_t
{
    /** @brief Size of RX buffer **/
    int m_rx_buffer_size;
    /** @brief Size of TX buffer **/
    int m_tx_buffer_size;
    /** @brief Size of UART queue **/
    int m_queue_size;
    /** @brief Flag for allocation the UART interrupt **/
    int m_intr_alloc_flags;
    /** @brief UARRT event handler **/
    QueueHandle_t * m_uart_queue;
    /** @brief Port number of UART **/
    uart_port_t m_uart_port_numb;
};
