# 设置最低CMake版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(ResourceWatcher)

# 查找并要求Protobuf库
find_package(Protobuf REQUIRED)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# # 如果存在proto目录，则生成C++源文件
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/proto")
#     protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
#     include_directories("${CMAKE_CURRENT_BINARY_DIR}/proto")
# endif()
set(PROTO_SRC "${CMAKE_CURRENT_SOURCE_DIR}/proto/system_data.proto")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC})
# 包含目录
include_directories(include proto ${Protobuf_INCLUDE_DIRS})

# 收集源文件
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 链接库
target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARIES})