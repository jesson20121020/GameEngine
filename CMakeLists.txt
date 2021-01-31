cmake_minimum_required(VERSION 3.1)

# 导出与平台无关的通用设置
message("开始导入平台无关通用配置")
include(cmake/common.cmake)
# 导入平台相关设置
message("开始导入平台相关配置")
include(cmake/platform.cmake)

# 设置工程名称
project(GameEngine)

# 以下添加子工程
add_subdirectory(client)
