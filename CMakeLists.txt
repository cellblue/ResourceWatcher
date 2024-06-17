cmake_minimum_required(VERSION 3.10)

project(ResourceWatcher)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fexceptions -frtti -fsanitize=address")

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

set(SOURCE_FILES
    src/main.cpp
    src/app.cpp
    src/watcher.cpp
    src/cpu_watcher.cpp
    src/timer_manager.cpp

)


include_directories(include proto)


# Generate protobuf files

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_SOURCE_DIR}/proto/system_data.proto)


# Add executable

add_executable(ResourceWatcher ${SOURCE_FILES} ${PROTO_SRCS})


# Link protobuf libraries

target_link_libraries(ResourceWatcher PRIVATE protobuf)