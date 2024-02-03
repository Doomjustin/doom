configure_file(Version.h.in Version.h)

# 这是个demo
add_library(doom STATIC
        Log.cpp
        Log.h
)

# 提供给用户的include目录
target_include_directories(doom INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/> # 允许使用相对路径，这里是相对于安装路径的相对路径
)

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
    $<$<CONFIG:Debug>:TEMPLATE_DEBUG> # 当有类似于DEBUG宏的东西时，很有用
)
