set(RESOURCES Assets.xcassets Base.lproj/LaunchScreen.storyboard Base.lproj/Main.storyboard)

# 添加源码文件编译可执行文件
add_executable(client MACOSX_BUNDLE
	main.m
	AppDelegate.h
	AppDelegate.m
	ViewController.h
	ViewController.m
	SceneDelegate.h
	SceneDelegate.m
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
	${CMAKE_CURRENT_LIST_DIR}/Info.plist
)

# 设置应用使用图标
set_target_properties(
	client
	PROPERTIES
    XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME 
	"AppIcon"
)


set(CMAKE_XCODE_ATTRIBUTE_DERIVE_MACCATALYST_PRODUCT_BUNDLE_IDENTIFIER "com.netease1.client")
# 添加Framework
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework UIKit")
# 设置处理器架构列表
set(CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD))
# 设置ios版本
set(CMAKE_OSX_DEPLOYMENT_TARGET 9.3)
