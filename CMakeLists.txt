cmake_minimum_required(VERSION 3.28)
project(socket_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB src_file "*.h" "*.cpp" "*.c")
file(GLOB client_src_file "client/*.h" "client/*.cpp" "client/*.c")
file(GLOB server_src_file "server/*.h" "server/*.cpp" "server/*.c")

# Tìm thư viện GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(Threads REQUIRED)

## If you need to use socket-related functions
#set(SOCKET_LIBRARIES "-lsocket")


# If you're on a Unix-like system (Linux, macOS)
if(UNIX)
    # Find the socket library
    find_library(SOCKET_LIBRARY NAMES socket)
    if(SOCKET_LIBRARY)
        message(STATUS "Found socket library: ${SOCKET_LIBRARY}")
        list(APPEND SOCKET_LIBRARIES ${SOCKET_LIBRARY})
    else()
        message(FATAL_ERROR "Socket library not found")
    endif()
endif()


# Đường dẫn đến các tiêu đề và thư viện của GTK
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(server ${src_file} ${server_src_file})

add_executable(client ${src_file} ${client_src_file})

# Liên kết thư viện GTK
#target_link_libraries(server PRIVATE  ${GTK3_LIBRARIES} ${SOCKET_LIBRARIES}  Threads::Threads)
#target_link_libraries(client PRIVATE  ${GTK3_LIBRARIES} ${SOCKET_LIBRARIES} Threads::Threads)


target_link_libraries(server PRIVATE  ${GTK3_LIBRARIES} wsock32 ws2_32 Threads::Threads)

target_link_libraries(client PRIVATE  ${GTK3_LIBRARIES} wsock32 ws2_32 Threads::Threads)
