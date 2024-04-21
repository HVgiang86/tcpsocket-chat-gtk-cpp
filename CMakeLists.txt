cmake_minimum_required(VERSION 3.22)
project(socket_client)

# Set the path to the RapidJson library
set(RAPIDJSON_INCLUDE_DIR /usr/include/rapidjson)  # Update this path if Crypto++ is installed elsewhere
set(RAPIDJSON_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)  # Update this path if Crypto++ is installed elsewhere

include_directories(${RAPIDJSON_INCLUDE_DIR})
find_library(RAPIDJSON_LIB rapidjson HINTS ${RAPIDJSON_LIBRARY_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB src_file "*.h" "*.cpp" "*.c")
file(GLOB client_src_file "client/*.h" "client/*.cpp" "client/*.c")
file(GLOB server_src_file "server/*.h" "server/*.cpp" "server/*.c")



# Tìm thư viện GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(Threads REQUIRED)


# Đường dẫn đến các tiêu đề và thư viện của GTK
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(server_bin ${src_file} ${server_src_file})

add_executable(client_bin ${src_file} ${client_src_file})

# Liên kết thư viện GTK
# Liên kết thư viện GTK và socket
target_link_libraries(server_bin PRIVATE ${GTK3_LIBRARIES} ${SOCKET_LIBRARIES} Threads::Threads)
target_link_libraries(client_bin PRIVATE ${GTK3_LIBRARIES} ${SOCKET_LIBRARIES} Threads::Threads)

