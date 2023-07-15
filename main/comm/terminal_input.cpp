#include "terminal_input.hpp"

/** see header **/
std::string Terminal::read_line_blocking(const TickType_t tick_to_wait)
{
    std::string data;

    static constexpr const uint32_t read_by_byte = 1;
    static constexpr const uint8_t new_line = '\n';

    while (true)
    {
        uint8_t value = 0;
        const auto readed_length = uart_read_bytes(m_uart_driver_conf.m_uart_port_numb,
                                                   &value, read_by_byte, tick_to_wait);
        if (readed_length == read_by_byte)
        {
            if (value == new_line)
            {
                break;
            }

            data += static_cast<char>(value);
        }
    }

    uart_flush(m_uart_driver_conf.m_uart_port_numb);
    return data;
}