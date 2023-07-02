# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v5.1-2/components/bootloader/subproject"
  "C:/chat_server_esp32/build/bootloader"
  "C:/chat_server_esp32/build/bootloader-prefix"
  "C:/chat_server_esp32/build/bootloader-prefix/tmp"
  "C:/chat_server_esp32/build/bootloader-prefix/src/bootloader-stamp"
  "C:/chat_server_esp32/build/bootloader-prefix/src"
  "C:/chat_server_esp32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/chat_server_esp32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/chat_server_esp32/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
