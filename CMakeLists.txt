cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# use common cmake
include(3rdparty/cmake/common.cmake)
include(3rdparty/cmake/utils.cmake)
include(3rdparty/cmake/platform.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include(CMakeDependentOption)

set(PYTHON_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${PYTHON_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_ROOT_DIR})


add_subdirectory(3rdparty/glfw)
include(3rdparty/imgui/imgui_lib.cmake)
add_subdirectory(runtime/client)

project(GameEngine VERSION 1.0.0)

# #[[ add_subdirectory(zlib)
# include(python/python_lib.cmake)
# include(python/python_exe.cmake)
# add_subdirectory(glfw)
# add_subdirectory(imgui)
# add_subdirectory(imgui_zmo)
# add_subdirectory(implot)
# # add_subdirectory(pyimgui)
# add_subdirectory(imgui_node_editor) ]]
