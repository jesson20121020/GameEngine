set(GLOBAL_RESOURCES Assets.xcassets)
set(BASE_RESOURCES Base.lproj/Main.storyboard)
set(RESOURCES ${GLOBAL_RESOURCES} ${BASE_RESOURCES})

# 添加源码文件编译可执行文件
add_executable(client MACOSX_BUNDLE
	main.m
	AppDelegate.h
	AppDelegate.m
	ViewController.h
	ViewController.m
	client.entitlements
	${RESOURCES}
)

# 设置需要放到Resources目录下的资源
set_source_files_properties(
	${RESOURCES}
	PROPERTIES
	MACOSX_PACKAGE_LOCATION
	Resources
)

# 设置Info.plist
set_target_properties(
    client
    PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST
	${CMAKE_CURRENT_LIST_DIR}/Info.plist.in
)

# 设置bundle identifier
set_target_properties(
	client
	PROPERTIES
	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER
	"com.netease.client"
)

# 设置应用使用图标
set_target_properties(
	client
	PROPERTIES
	XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME 
	"AppIcon"
)

# 添加Framework
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
