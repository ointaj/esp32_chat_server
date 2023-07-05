/**
 * @file   output.hpp
 * @author Oliver Sintaj
 * @date   2023
 * @brief  Support for terminal output
 */


/** @brief ESP-IDF headers **/
#include "esp_log.h"

/** @brief Standard headers**/
#include <utility>
#include <type_traits>
#include <string>
#include <cstdlib>

/** @brief App headers **/
#include "app_configuration.hpp"


/** @brief Enum represents logging level **/
enum class e_LogType : uint8_t
{
    Info,
    Warn,
    Error
};

/**
* @brief Local function for terminal ouput casting
* @param args All arguments to be printed
* @return converted argumetns to one string
* **/
#ifdef TERMINAL_OUTPUT
template<typename T>
static std::string args_to_string(T && arg)
{
    if constexpr (std::is_same_v<std::decay_t<T>, const char*> ||
                  std::is_same_v<std::decay_t<T>, char*> ||
                  std::is_same_v<std::decay_t<T>, std::string>)
    {   
        return std::forward<T>(arg);
    }
    else
    {
        return std::to_string(std::forward<T>(arg));
    }
}
#endif // TERMINAL_OUTPUT

/** @brief Class that supports terminal output **/
class Output final
{
    public:
        /**
         * @brief Variadic template member function for terminal ouput (logging)
         * @param log_type Log level
         * @param tag      Tag name
         * @param args     All arguments to be printed
         * @return non
         * **/
        template <typename ... Args>
        static inline void log(e_LogType log_type,
                               const char * tag,
                               Args &&... args)
        {
#ifdef TERMINAL_OUTPUT
            const auto log_message = ((args_to_string(std::forward<Args>(args)) + ...));
            
            switch (log_type)
            {
                case e_LogType::Info:
                {
                    ESP_LOGI(tag, "%s", log_message.c_str());
                    break;
                }
                case e_LogType::Warn:
                {
                    ESP_LOGW(tag, "%s", log_message.c_str());
                    break;
                }
                case e_LogType::Error:
                {
                    ESP_LOGE(tag, "%s", log_message.c_str());
                    break;
                }
                default:
                {
                    abort();
                    break;
                }
            }
#endif // TERMINAL_OUTPUT
        }
};