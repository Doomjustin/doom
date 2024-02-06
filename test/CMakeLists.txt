#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# 开启CMake的测试框架
#enable_testing()
#include(Catch)
#include(CTest)

#function(add_catch2_test TARGET SOURCE)
#    add_executable(${TARGET} ${SOURCE})
#
#    target_link_libraries(${TARGET} PRIVATE
#        Catch2::Catch2WithMain
#    )
#    catch_discover_tests(${TARGET})
#endfunction()


add_executable(test-log test_log.cpp)
target_link_libraries(test-log PRIVATE doom)

add_executable(test-config test_config.cpp)
target_link_libraries(test-config PRIVATE doom)
