#include "spiffs_operation_handle.hpp"

/** see header **/
std::string SPIFFSOperationHandle::read()
{
    // Check if file is ok to be read from, file is open and its not empty
    if ((!is_file_open()) || (!_current_mode(READ_MODE)) || (0 < m_file_size))
    {
        return {};
    }

    std::string data(m_file_size, '\0');
    fread(data.data(), 1, data.length(), m_file_handler);

    return data;
}

