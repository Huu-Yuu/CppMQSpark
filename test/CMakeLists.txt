cmake_minimum_required(VERSION 3.10)
project(mqspark_tests)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(
    ./
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/CppMQSpark
    /users/csgdri/csgems/source/lib/linux64
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

add_executable(${PROJECT_NAME}
    main.cpp
    consumer.h
    producer.h
)

target_link_libraries(${PROJECT_NAME}
#    -lCppMQSpark
    -lpthread
)


