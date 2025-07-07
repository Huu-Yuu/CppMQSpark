cmake_minimum_required(VERSION 3.28)
project(CppMQSpark)

set(CMAKE_CXX_STANDARD 11)
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置头文件搜索路径
include_directories(
        ${PROJECT_SOURCE_DIR}/include/CppMQSpark
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/utils
)
add_library(${PROJECT_NAME} SHARED
        src/cppmqspark.cpp
        src/cppmqspark.h
        include/CppMQSpark/mqspark_abstract.h
        include/CppMQSpark/message_interface.cpp
        include/CppMQSpark/message_interface.h
        src/abstract_manager.h
        src/topic_manager.cpp
        src/topic_manager.h
        src/topic.cpp
        src/topic.h
        src/utils/public_macro.h
)
#add_executable(C__MQSpark main.cpp)
install(DIRECTORY include/ DESTINATION include)
#控制动态库的符号导出（Windows必需）
target_compile_definitions(${PROJECT_NAME} PRIVATE CppMQSpark_LIBRARY)