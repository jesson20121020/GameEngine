set(TARGET client)
set(PLATFORM "")
set(HEADER_FILES Scene.h Shader.h glheader.h FileUtils.h)
set(SOURCE_FILES
    Model.cpp
    Model001.cpp
    Model002.cpp
    Model003.cpp
    Model004.cpp
    Model005.cpp
    Camera.cpp
    Scene.cpp
    Shader.cpp
    stb_image.cpp
    FileUtils.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/backends/imgui_impl_opengl3.cpp)
set(RESOURCE_FILES)
set(THIRD_DEPENDS)
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/include
    ${CMAKE_SOURCE_DIR}/dependencies/imgui
    ${CMAKE_SOURCE_DIR}/dependencies/glm-0.9.8.5/)
set(THIRD_DEPEND_DIRS)
set(THIRD_DEPEND_BINS)
set(BINARY_OUPUT_DIR)
set(FRAMEWORK_FILES)
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/client/res)

file(GLOB RES_FILES res/*)
foreach(filename ${RES_FILES})
  list(APPEND RESOURCE_FILES ${filename})
endforeach()

message(${CMAKE_CURRENT_BINARY_DIR})

if(PLATFORM_IOS)
  message("todo")

elseif(PLATFORM_WINDOWS)
  set(PLATFORM WIN32)
  set(CMAKE_BUILD_TYPE Debug)
  list(
    APPEND
    HEADER_FILES
    windows/client.h
    windows/framework.h
    windows/Resource.h
    windows/targetver.h
    windows/FileUtils-Win.h)
  list(APPEND SOURCE_FILES windows/client.cpp)
  list(APPEND SOURCE_FILES windows/FileUtils-Win.cpp
       ${CMAKE_SOURCE_DIR}/dependencies/imgui/backends/imgui_impl_win32.cpp)
  list(APPEND RESOURCE_FILES windows/client.rc windows/client.ico
       windows/small.ico)
  list(APPEND THIRD_DEPENDS opengl32.lib glu32.lib glew32.lib)
  list(APPEND THIRD_DEPEND_DIRS
       ${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/x64)
  list(APPEND THIRD_DEPEND_BINS
       ${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/bin/Release/x64/)
  set(BINARY_OUPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
elseif(PLATFORM_OSX)
  set(PLATFORM MACOSX_BUNDLE)
  set(CMAKE_BUILD_TYPE Debug)
  # 添加Framework
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
  list(APPEND HEADER_FILES mac/OGLView.h mac/OGLMainWindow.h mac/AppDelegate.h
       mac/FileUtils-Mac.h)
  list(
    APPEND
    SOURCE_FILES
    mac/main.mm
    mac/AppDelegate.mm
    mac/OGLView.mm
    mac/OGLMainWindow.mm
    mac/FileUtils-Mac.mm
    mac/client.entitlements
    ${PROJECT_SOURCE_DIR}/dependencies/imgui/backends/imgui_impl_osx.mm)
  list(APPEND RESOURCE_FILES mac/Assets.xcassets)
  list(APPEND THIRD_DEPENDS libGLEW.a)
  list(APPEND THIRD_DEPEND_DIRS
       ${CMAKE_SOURCE_DIR}/dependencies/glew-2.2.0/lib/mac)
  list(APPEND THIRD_DEPEND_BINS
       ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0/lib/mac)
  set(BINARY_OUPUT_DIR
      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/game.app/Contents/MacOS
  )

  # 设置需要放到Resources目录下的资源 set_source_files_properties(${RESOURCES} PROPERTIES
  # MACOSX_PACKAGE_LOCATION Resources)

  file(GLOB FRAMEWORK_FILES
       ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0/lib/mac/*.dylib)
  foreach(framework ${FRAMEWORK_FILES})
    set_source_files_properties(${framework} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                        Frameworks)
    set_source_files_properties(${framework} PROPERTIES XCODE_FILE_ATTRIBUTES
                                                        "CodeSignOnCopy")
  endforeach()

  file(GLOB RES_FILES ${RESOURCE_FILES})
  foreach(filename ${RES_FILES})
    message(${filename})
    set_source_files_properties(${filename} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                       Resources)
  endforeach()
endif()

include_directories(${INCLUDE_DIRS})
link_directories(${THIRD_DEPEND_DIRS})

source_group("Resources" FILES ${RESOURCE_FILES})
source_group("Frameworks" FILES ${FRAMEWORK_FILES})
add_executable(${TARGET} ${PLATFORM} ${HEADER_FILES} ${SOURCE_FILES}
                         ${RESOURCE_FILES} ${FRAMEWORK_FILES})
if(FRAMEWORK_FILES)
  set_target_properties(
    ${TARGET} PROPERTIES XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS
                         "@executable_path/Frameworks")
endif()

if(PLATFORM_WINDOWS)
  target_link_libraries(${TARGET} ${THIRD_DEPENDS})
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${THIRD_DEPEND_BINS}
            ${BINARY_OUPUT_DIR})
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/client/res
            ${BINARY_OUPUT_DIR}/Resources)
elseif(PLATFORM_OSX)
  target_link_libraries(${TARGET} ${THIRD_DEPENDS}
                        "-framework OpenGL -framework GameController")
  # NOTE: 通过install_name_tool解决dylib not found的问题
  add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND
      install_name_tool -change "/usr/local/lib/libGLEW.2.2.0.dylib"
      "@executable_path/../Frameworks/libGLEW.2.2.0.dylib"
      "$BUILT_PRODUCTS_DIR/$EXECUTABLE_PATH")
endif()

if(PLATFORM_OSX)
  # 设置应用使用图标
  set_target_properties(
    client PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME
                      "AppIcon")

  set_target_properties(
    ${TARGET}
    PROPERTIES MACOSX_BUNDLE_INFO_PLIST
               ${PROJECT_SOURCE_DIR}/client/mac/Info.plist.in
               # name
               XCODE_ATTRIBUTE_PRODUCT_NAME "game"
               # version
               XCODE_ATTRIBUTE_PRODUCT_VERSION "1.0.1"
               # build
               XCODE_ATTRIBUTE_PRODUCT_BUILD_VERSION 1001
               # bundle identifier
               XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.netease.client")
endif()
