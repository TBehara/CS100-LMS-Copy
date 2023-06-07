CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(LMS)

set(CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_EXECUTABLE(LMS 
    src/main.cpp
    src/LMS.cpp
    src/search_base.cpp
    src/jsonManager.cpp
    src/user.cpp
    src/admin.cpp
    src/book.cpp
    src/LMS.cpp
    libraries/hash/sha256.cpp
)

TARGET_LINK_LIBRARIES(LMS
    stdc++fs
)