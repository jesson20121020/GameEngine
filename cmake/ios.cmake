# 这里设置一些ios平台独有的设置


# 设置cmake编译系统为IOS
set(CMAKE_SYSTEM_NAME "iOS")

# 设置支持的最低ios系统版本号
set(CMAKE_OSX_DEPLOYMENT_TARGET "9.1" CACHE STRING "最低IOS部署版本")
# 这里有效平台
#set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
