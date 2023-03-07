cmake_minimum_required(VERSION 3.14)
project(ASEmoji)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        sources/emoji.cpp
        )

set(HEADERS
        sources/emoji.h
        ASEmoji.h
        )

add_library(ASEmoji ${SOURCES} ${HEADERS})

target_include_directories(
        ASEmoji PUBLIC ${PROJECT_SOURCE_DIR}
)
