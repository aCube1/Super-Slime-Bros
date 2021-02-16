cmake_minimum_required(VERSION 3.16)
project(slime)

set(CMAKE_C_FLAGS "-pedantic -Wall")
set(CMAKE_C_STANDARD 99)

set(BASE_INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src/Core)
add_subdirectory(src/System)

file(GLOB SRCS "src/*.c")

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} CB_Core CB_System)
