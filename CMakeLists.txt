CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(LMS)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_EXECUTABLE(LMS 
    src/main.cpp
    src/jsonManager.cpp
    src/user.cpp
    src/book.cpp
    src/LMS.cpp
    libraries/hash/sha256.cpp
)