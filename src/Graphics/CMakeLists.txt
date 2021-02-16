set(MODULE_NAME CB_Graphics)

file(GLOB SRCS "*.c")

add_library(${MODULE_NAME} STATIC ${SRCS})

target_link_libraries(${MODULE_NAME} SDL2)
target_include_directories(${MODULE_NAME} PUBLIC ${BASE_INCLUDE_DIRECTORY})
