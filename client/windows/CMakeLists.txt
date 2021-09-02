
add_executable(
  client WIN32
  client.cpp
  client.h
  framework.h
  Resource.h
  targetver.h
  client.rc
  client.ico
  small.ico
  ../Scene.h
  ../Scene.cpp
  ../Shader.h
  ../Shader.cpp
  )

include_directories(../)

message("${OPENGL_LIBRARIES}")

target_link_libraries(client opengl32.lib glu32.lib)

# add_custom_command(TARGET client POST_BUILD_COMMAND ${CMAKE_COMMAND} -E
# copy_directory "${PROJECT_SOURCE_DIR}/dependencies/glew-2.1.0/bin/Release/x64"
# "$<TARGET_FILE_DIR:client>")

source_group("Resources" FILES client.rc client.ico small.ico)
