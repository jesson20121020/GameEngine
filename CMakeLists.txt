cmake_minimum_required(VERSION 3.1)

# 导出与平台无关的通用设置
message("开始导入平台无关通用配置")
include(cmake/common.cmake)
# 导入平台相关设置
message("开始导入平台相关配置")
include(cmake/platform.cmake)

# 设置工程名称
project(GameEngine)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 以下添加子工程
add_subdirectory(client)

