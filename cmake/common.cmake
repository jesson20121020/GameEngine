# 与平台无关的通用配置

# 设置c/c++支持的特性
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# 默认不生成zero_check工程
set(CMAKE_SUPPRESS_REGENERATION ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set_property(GLOBAL PROPERTY CMAKE_SKIP_PACKAGE_ALL_DEPENDENCIY ON)
