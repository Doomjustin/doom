set(DOOM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)

configure_file(Version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Version.h)

add_library(doom STATIC
        Log.cpp
        Log.h
        Charset.h
        log/LogAppender.h
        log/LogFormatter.cpp
        log/LogFormatter.h
        log/LogLevel.h
        log/LogEvent.h
        log/Logger.cpp
        log/Logger.h
        log/StdoutLogAppender.cpp
        log/StdoutLogAppender.h
        log/FileLogAppender.cpp
        log/FileLogAppender.h
        log/LogLevel.cpp
)

# 提供给用户的include目录
target_include_directories(doom INTERFACE
    $<BUILD_INTERFACE:${DOOM_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include/> # 允许使用相对路径，这里是相对于安装路径的相对路径
)

target_include_directories(doom PUBLIC ${DOOM_INCLUDE_DIR})

# 开启编译器features和options
target_link_libraries(doom PUBLIC cpp-compiler-flags)

set_target_properties(doom PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF # 仅对实际编译的target有效，禁用compiler的拓展，使用pure C++ std
        INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
        INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO FALSE
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
        INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
)

# 添加第三方库
#target_link_libraries(doom PUBLIC
#    fmt::fmt
#    spdlog::spdlog
#    nlohmann_json::nlohmann_json
#)

# 如果是Debug构建，则添加对应的定义
target_compile_definitions(doom PUBLIC
    $<$<CONFIG:Debug>:DOOM_DEBUG> # 当有类似于DEBUG宏的东西时，很有用
)
