cmake_minimum_required(VERSION 3.16)
project(slime)

set(CMAKE_C_FLAGS "-pedantic -Wall")
set(CMAKE_C_STANDARD 99)

set(BASE_INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/ext/stb)

add_subdirectory(src/Core)
add_subdirectory(src/System)
add_subdirectory(src/Graphics)

file(GLOB SRCS "src/*.c")

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} CB_Core CB_System CB_Graphics m)
