cmake_minimum_required(VERSION 3.10)

project(ResourceWatcher)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS False)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fexceptions -frtti -fsanitize=address")

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

set(SRC_DIR src)
set(UTILITY_DIR utility)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE UTILITY_HEADERS "${UTILITY_DIR}/*.hpp")


include_directories(include proto utility)


# Generate protobuf files

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_SOURCE_DIR}/proto/system_data.proto)


# Add executable

add_executable(ResourceWatcher ${SRC_FILES} ${UTILITY_HEADERS} ${PROTO_SRCS})


# Link protobuf libraries

target_link_libraries(ResourceWatcher PRIVATE protobuf)