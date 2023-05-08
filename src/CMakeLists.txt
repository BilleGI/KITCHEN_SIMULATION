cmake_minimum_required(VERSION 3.5)

add_executable(cocina main.cpp ${MY_INCLUDE_DIR}/waiter.h waiter.cpp
    ${MY_INCLUDE_DIR}/kitchen.h kitchen.cpp ${MY_INCLUDE_DIR}/courier.h courier.cpp)

target_include_directories(cocina PUBLIC ${MY_INCLUDE_DIR})
