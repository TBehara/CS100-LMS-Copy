CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(LMSTests
    test.cpp
    ../src/user.cpp
    ../src/book.cpp
    ../src/search_base.cpp
    ../src/admin.cpp
    ../libraries/hash/sha256.cpp
)

target_link_libraries(LMSTests gmock gtest gtest_main)