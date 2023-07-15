#pragma once

/**
 * @file   terminal_conf.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  All needed configuratuion for terminal
 */

#include "driver/uart.h"

/** @brief Default terminal baud rate for UART **/
inline constexpr int TERMINAL_BAUD_RATE = 115200;

/** @brief Default terminal UART threshold for RTS **/
inline constexpr uint8_t TERMINAL_UART_THRESHOLD_RTS = 122;

/** @brief Default terminal UART ref tick **/
inline constexpr bool TERMINAL_UART_REF_TICK = false;

/** @brief Default terminal size of RX buffer **/
inline constexpr int TERMINAL_RX_BUFF_SIZE = 1024;

/** @brief Default terminal size of TX buffer **/
inline constexpr int TERMINAL_TX_BUFF_SIZE = 0;

/** @brief Default terminal size of UART queue  **/
inline constexpr int TERMINAL_QUEUE_SIZE= 0;

/** @brief Default terminal flag for allocation the UART interrupt **/
inline constexpr int TERMINAL_INTR_ALLOC_FLAG = 0;

/** @brief Default terminal UART port **/
inline constexpr uart_port_t TERMINAL_UART_PORT = UART_NUM_0;
