set(TARGET client)
set(PLATFORM "")
set(HEADER_FILES Scene.h Shader.h glheader.h)
set(SOURCE_FILES Scene.cpp Shader.cpp)
set(RESOURCE_FILES)
set(THIRD_DEPENDS)
set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/include)
set(THIRD_DEPEND_DIRS)
set(THIRD_DEPEND_BINS)
set(BINARY_OUPUT_DIR)
if(PLATFORM_IOS)
  message("todo")

elseif(PLATFORM_WINDOWS)
  set(PLATFORM WIN32)
  set(CMAKE_BUILD_TYPE Debug)
  list(APPEND HEADER_FILES windows/client.h windows/framework.h
       windows/Resource.h windows/targetver.h)
  list(APPEND SOURCE_FILES windows/client.cpp)
  list(APPEND RESOURCE_FILES windows/client.rc windows/client.ico
       windows/small.ico)
  list(APPEND THIRD_DEPENDS opengl32.lib glu32.lib glew32.lib)
  list(APPEND THIRD_DEPEND_DIRS
       ${CMAKE_SOURCE_DIR}/dependencies/glew-2.1.0/lib/Release/x64)
  list(APPEND THIRD_DEPEND_BINS
       ${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/bin/Release/x64/)
  list(APPEND THIRD_DEPEND_BINS
       ${PROJECT_SOURCE_DIR}/client/res)
  set(BINARY_OUPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
elseif(PLATFORM_OSX)
  set(PLATFORM MACOSX_BUNDLE)
  set(CMAKE_BUILD_TYPE Debug)
  # 添加Framework
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
  list(APPEND HEADER_FILES mac/OGLView.h mac/OGLMainWindow.h mac/AppDelegate.h)
  list(
    APPEND
    SOURCE_FILES
    mac/main.mm
    mac/AppDelegate.mm
    mac/OGLView.mm
    mac/OGLMainWindow.mm
    mac/client.entitlements)
  list(APPEND RESOURCE_FILES mac/Assets.xcassets)
  list(APPEND THIRD_DEPENDS libGLEW.a)
  list(APPEND THIRD_DEPEND_DIRS
       ${CMAKE_SOURCE_DIR}/dependencies/glew-2.2.0/lib/mac)
  list(APPEND THIRD_DEPEND_BINS
       ${PROJECT_SOURCE_DIR}/dependencies/glew-2.2.0/lib/mac)
  set(BINARY_OUPUT_DIR
      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/game.app/Contents/MacOS
  )

  # 设置需要放到Resources目录下的资源
  set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                      Resources)

endif()

include_directories(${INCLUDE_DIRS})
link_directories(${THIRD_DEPEND_DIRS})

source_group("Resources" FILES ${RESOURCE_FILES})
add_executable(${TARGET} ${PLATFORM} ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})
target_link_libraries(${TARGET} ${THIRD_DEPENDS} "-framework OpenGL")
add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${THIRD_DEPEND_BINS}
          ${BINARY_OUPUT_DIR})

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
