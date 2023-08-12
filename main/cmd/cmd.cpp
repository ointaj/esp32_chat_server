#include "cmd.hpp"
#include "nvs_values.hpp"

/** see header **/
esp_err_t CMD::set_wifi_credentials()
{
    auto & terminal = InputTerminal::get_instance();
    auto nvs = NVSOperationHandle::create(NVS_DEFUAULT_NAMESPACE,
                                          NVS_READWRITE);

    Output::log(e_log_type::et_INFO, m_TAG, "Please, enter SSID :");
    const auto ssid = terminal.read_line_blocking();

    Output::log(e_log_type::et_INFO, m_TAG, "Please, enter password :");
    const auto password = terminal.read_line_blocking();

    const s_wifi_credentials_t wifi = {
        .m_ssid = ssid,
        .m_password = password
    };

    return nvs.write_to_nvs_storage_blob(NVS_WIFI_CREDENTIALS_KEY, &wifi);
}