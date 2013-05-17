cmake_minimum_required(VERSION 2.8.9)

project(xps)

set (HEADER_FILES
  include/Process.h
  include/ProcessList.h
)

set (SOURCE_FILES
  src/main.cpp
)

#
# platform specific files
#

if (WIN32)
  set (PLATFORM_SOURCE_FILES
    src/win/ProcessListImpl.cpp
  )
elseif (APPLE)
  set (PLATFORM_SOURCE_FILES
    src/osx/ProcessListImpl.cpp
  )

elseif (UNIX)
  set (PLATFORM_SOURCE_FILES
      src/linux/ProcessListImpl.cpp
  )
endif ()

include_directories(include)
add_executable(xps ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_SOURCE_FILES})
