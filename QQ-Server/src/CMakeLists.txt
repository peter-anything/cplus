# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

add_subdirectory(controller)
include_directories(controller)

set (EXTRA_LIBS ${EXTRA_LIBS} controller)
# 指定生成目标
add_executable(Demo ${DIR_SRCS})
target_link_libraries (Demo ${EXTRA_LIBS})