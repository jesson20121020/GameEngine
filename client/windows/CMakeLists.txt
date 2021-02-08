

add_executable(client WIN32
	client.cpp
	client.h
	framework.h
	Resource.h
	targetver.h
	client.rc
	client.ico
	small.ico
)


source_group("Resources" FILES client.rc client.ico small.ico)
