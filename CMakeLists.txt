cmake_minimum_required(VERSION 3.6)

project(IoT)

set(CMAKE_C_STANDARD 99)

# paths are somewhat different when using cygwin
include_directories("$ENV{CYGWIN_JAVA_HOME}/include" "$ENV{CYGWIN_JAVA_HOME}/include/win32")

set(HEADER_FILES JniInterface.h common.h library.h)
set(SOURCE_FILES JniInterface.c common.c library.c)

add_library(IoT SHARED ${SOURCE_FILES} ${HEADER_FILES})
