# 平台设置相关, 根据平台类型Include对应平台的cmake配置文件

if (APPLE)
	set(PLATFORM_OSX ON)
elseif (WIN32)
	set(PLATFORM_WINDOWS ON)
endif()

if (PLATFORM_IOS)
	message("当前为IOS平台")
	include(cmake/ios.cmake)
elseif (PLATFORM_OSX)
	message("当前为OSX平台")
	include(cmake/mac.cmake)
elseif(PLATFORM_WINDOWS)
	message("当前为Windows平台")
endif()
