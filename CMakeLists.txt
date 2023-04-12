cmake_minimum_required(VERSION 3.24)
set(CMAKE_PROJECT_NAME CMAKE-TEMPLATE)
Project(${CMAKE_PROJECT_NAME} C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)

find_package(OpenGL REQUIRED)

add_subdirectory(
    deps/glfw
)

add_subdirectory(
    ${LIB_DIR}/freetype
)

set(SRC
    src/main.cpp
)


add_executable(${CMAKE_PROJECT_NAME} ${SRC})


add_library(glad deps/glad/include/glad/glad.h deps/glad/src/glad.c)


include_directories(
        deps/glad/include
        deps/glm
        deps/freetype/include
        ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glad
        ${OPENGL_LIBRARIES}
        ${EXTRA_LIBS}
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})


