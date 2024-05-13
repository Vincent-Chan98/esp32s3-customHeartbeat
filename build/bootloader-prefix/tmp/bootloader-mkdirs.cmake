# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp/esp-idf/components/bootloader/subproject"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix/tmp"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix/src"
  "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Data/Desktop/Vincent/Testing/usingESPIDF/ESPIDF/esp32s3_heartbeat/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
