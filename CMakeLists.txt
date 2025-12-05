cmake_minimum_required(VERSION 3.28)
project(CppMQSpark)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 根据版本定义不同宏
if(CMAKE_CXX_STANDARD EQUAL 14)
    add_compile_definitions(USING_CPP14=1)
elseif(CMAKE_CXX_STANDARD EQUAL 11)
    add_compile_definitions(USING_CPP11=1)
endif()

# 解决 mingw 汇编器不支持特定调试选项的问题
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # 移除所有现有的 -gdwarf-* 选项
    string(REGEX REPLACE "-gdwarf-[0-9]+" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    # 添加通用的 -g 选项
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# 设置动态库/静态库生成路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 设置头文件搜索路径
include_directories(
        ${PROJECT_SOURCE_DIR}/include/CppMQSpark
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/utils
)
#库文件名称 全小写
set(LIB_NAME cppmqspark)
add_library(${LIB_NAME} SHARED
        src/cppmqspark.cpp
        src/cppmqspark.h
        src/mqspark_abstract.cpp
        include/CppMQSpark/mqspark_abstract.h           # 外部include 接口
        include/CppMQSpark/message_interface.cpp
        include/CppMQSpark/message_interface.h          # 外部include 接口
        src/abstract_manager.h
        src/topic_manager.cpp
        src/topic_manager.h
        src/topic.cpp
        src/topic.h
        src/utils/public_macro.h
)

###test 测试代码
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(mqspark_tests
        test/main.cpp
        test/consumer.h
        test/producer.h

        src/cppmqspark.cpp
        src/cppmqspark.h
        src/mqspark_abstract.cpp
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
target_link_libraries(mqspark_tests -lpthread)
###test 测试代码

install(DIRECTORY include/CppMQSpark/ DESTINATION include/CppMQSpark
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.cpp" EXCLUDE
)

install(TARGETS ${LIB_NAME}
        EXPORT CppMQSparkTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)
#控制动态库的符号导出（Windows必需）
target_compile_definitions(${LIB_NAME} PRIVATE CppMQSpark_LIBRARY)
