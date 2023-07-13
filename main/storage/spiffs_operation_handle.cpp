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

/** see header **/
bool SPIFFSOperationHandle::write(std::string_view data)
{
    bool res = false;

    if ((is_file_open()) && (_current_mode(WRITE_MODE)) && !data.empty())
    {
        const auto writen_size = fwrite(data.data(), 1,
                                        data.size(), m_file_handler);
        if (writen_size == data.size())
        {
            res = true;
        }
        Output::esp_errno_output(m_TAG, res);
    }
    return res;
}

/** see header **/
bool SPIFFSOperationHandle::append(std::string_view data)
{
    bool res = false;

    if ((is_file_open()) && (_current_mode(APPEND_MODE)) && !data.empty())
    {
        const auto writen_size = fwrite(data.data(), 1,
                                        data.size(), m_file_handler);
        if (writen_size == data.size())
        {
            res = true;
        }
        Output::esp_errno_output(m_TAG, res);
    }
    return res;
}

/** see header **/
bool SPIFFSOperationHandle::seek(int64_t position,
                                 int32_t whence)
{
    bool res = false;
    if ((is_file_open()) && (0 != position))
    {
        const auto fseek_res = fseek(m_file_handler, position, whence);

        if (0 == fseek_res)
        {
            res = true;
        }
        Output::esp_errno_output(m_TAG, res);
    }

    return res;
}

/** see header **/
bool SPIFFSOperationHandle::remove()
{
    bool res = false;
    if (is_file_open())
    {
        const auto unlink_res = unlink(m_file_name.c_str());
        if (0 == unlink_res)
        {
            res = true;
            // Setting handler to point to nothing
            m_file_handler = nullptr;
        }
        Output::esp_errno_output(m_TAG, res);
    }

    return res;
}


/** see header **/
bool SPIFFSOperationHandle::change_file_name(std::string && new_filename)
{
    bool res = false;

    auto l_new_filename = std::move(new_filename);

    if ((is_file_open()) && (!l_new_filename.empty()))
    {
        if (!_starts_with_default_path(l_new_filename))
        {
            l_new_filename = std::string(m_default_path) + l_new_filename;
        }

        const auto rename_res = rename(m_file_name.c_str(), l_new_filename.c_str());
        if (0 == rename_res)
        {
            res = true;
            // Setting new path
            m_file_name = std::move(l_new_filename);
        }
        Output::esp_errno_output(m_TAG, res);
    }
    
    return res;
}
