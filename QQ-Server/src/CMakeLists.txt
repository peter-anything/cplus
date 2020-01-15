# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

add_subdirectory(./controller)
add_subdirectory(./crypto)

include_directories(./controller)
include_directories(./models)
include_directories(./crypto)
include_directories(./tools)
include_directories(./db)
# 指定生成目标
add_executable(Demo ${DIR_SRCS})

include_directories("/usr/include")

target_link_libraries (Demo controller crypto mysqlcppconn cryptopp)