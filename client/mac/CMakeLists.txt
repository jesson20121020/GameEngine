# 资源
set(RESOURCES Assets.xcassets)

# 添加源码文件编译可执行文件
add_executable(
  client MACOSX_BUNDLE
  main.mm
  AppDelegate.h
  AppDelegate.mm
  OGLMainWindow.h
  OGLMainWindow.mm
  OGLView.h
  OGLView.mm
  client.entitlements
  ../Scene.h
  ../Scene.cpp
  ../Shader.h
  ../Shader.cpp
  ${RESOURCES})

# 设置需要放到Resources目录下的资源
set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION
                                                    Resources)

# 设置应用使用图标
set_target_properties(
  client PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME
                    "AppIcon")

# 设置xcode工程相关属性
set_target_properties(
  client
  PROPERTIES # info.plist
             MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/Info.plist.in
             # name
             XCODE_ATTRIBUTE_PRODUCT_NAME "game"
             # version
             XCODE_ATTRIBUTE_PRODUCT_VERSION "1.0.1"
             # build
             XCODE_ATTRIBUTE_PRODUCT_BUILD_VERSION 1001
             # bundle identifier
             XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.netease.client")

# 添加Framework
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")

# 添加链接库
target_link_libraries(client "-framework OpenGL")
