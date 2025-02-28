add_library(ASEmoji::ASEmoji STATIC IMPORTED)

set_target_properties(ASEmoji::ASEmoji PROPERTIES
        IMPORTED_LOCATION "${CMAKE_INSTALL_PREFIX}/lib/libASEmoji.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include/ASEmoji"
)
