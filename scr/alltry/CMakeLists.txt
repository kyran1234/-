cmake_minimum_required(VERSION 3.24)
project(Dino_Clion C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_COMPILER "D:\\program\\MinGW\\bin\\gcc.exe")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O3 -g3 -Wall")
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_CXX_COMPILER             "D:\\program\\MinGW\\bin\\gcc.exe") # 填写绝对路径
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

#SDL2所在目录
set(SDL2_DIR D:\SDL\SDL2-devel-2.28.5-mingw\SDL2-2.28.5\x86_64-w64-mingw32)
#SDL2 Image所在目录
set(SDL2IMAGE_DIR D:\SDL\SDL2_image-devel-2.6.3-mingw\SDL2_image-2.6.3\x86_64-w64-mingw32)
#SDL2 ttf所在目录

#SDL2 mixer所在目录
# include目录
include_directories(${SDL2_DIR}/include/SDL2)
include_directories(${SDL2IMAGE_DIR}/include/SDL2)


#库目录
link_directories(${SDL2_DIR}/lib)
link_directories(${SDL2IMAGE_DIR}/lib)

# 库
link_libraries(mingw32 SDL2main SDL2 SDL2_image )

aux_source_directory(./ SRC) #源文件目录(当前目录设置到变量DIR_SRC)
add_executable(HelloWorld WIN32 ${SRC})
target_sources(HelloWorld  PRIVATE ${DIR_SRC})