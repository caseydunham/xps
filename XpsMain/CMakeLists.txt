cmake_minimum_required(VERSION 2.8.9)

project(xps)

set (HEADER_FILES
  include/Process.h
  include/ProcessList.h
)

set (SOURCE_FILES
  src/main.cpp
  src/linux/ProcessListImpl.cpp
)

include_directories(include)
add_executable(xps ${HEADER_FILES} ${SOURCE_FILES})
