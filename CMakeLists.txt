cmake_minimum_required(VERSION 3.17)
project(UserManagement)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/hashlib++/includes)  # 指定头文件搜索路径，该目录下面有 hl_hashwrapper.h hl_wrapperfactory.h hl_exception.h hl_md5.h hl_md5wrapper.h hl_sha1.h hl_sha1wrapper.h hl_sha2mac.h hl_sha256.h hl_sha256wrapper.h hl_sha2ext.h hl_sha384wrapper.h  hl_sha512wrapper.h hl_types.h hashlibpp.h
link_directories(${CMAKE_SOURCE_DIR}/dependencies/hashlib++)   # 指定使用的外部库的搜索路径，该目录下面有 libhl++.a

add_executable(UserManagement main.cpp UserManagement.cpp UserManagement.h)
target_link_libraries(UserManagement hl++ ) # 指定要连接的静态库. 会去搜索 libhl++.a, libhl++,so 或者 libhl++.dyld
