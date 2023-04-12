cmake_minimum_required(VERSION 3.24)
Project(Learning C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(
    deps/glfw
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)

find_package(OpenGL REQUIRED)

add_subdirectory(
    ${LIB_DIR}/freetype
)

set(SRC
    src/main.cpp
)


add_executable(Learning ${SRC})


add_library(glad deps/glad/include/glad/glad.h deps/glad/src/glad.c)


include_directories(
        deps/glad/include
        deps/glm
        deps/freetype/include
        ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(Learning
        glfw
        glad
        ${OPENGL_LIBRARIES}
        ${EXTRA_LIBS}
)

target_link_libraries(Learning ${FREETYPE_LIBRARIES})
target_include_directories(Learning PRIVATE ${FREETYPE_INCLUDE_DIRS})


