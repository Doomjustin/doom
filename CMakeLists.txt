cmake_minimum_required(VERSION 3.21)

project(doom
	VERSION 1.0
	LANGUAGES C CXX
)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	# Release
endif ()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(CppStandard)
# include(Submodule)

# 当且仅当这是主项目时，构建测试
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(test)
endif()

add_subdirectory(src/doom)
