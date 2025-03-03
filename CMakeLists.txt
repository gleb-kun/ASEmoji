cmake_minimum_required(VERSION 3.14)
project(ASEmoji)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        sources/ASEmoji.cpp
        sources/EmojiData.cpp
        )

set(HEADERS
        headers/ASEmoji.h
        headers/EmojiData.h
        )

add_library(ASEmoji STATIC ${SOURCES} ${HEADERS})

target_include_directories(
        ASEmoji PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers
)
