# AS::Emoji
[AS Universal Library] Emoji module

## About

:heart::fist::v:

Emoji for C++ Developers.
List of supported emoji in [EmojiList.md](\EmojiList.md).
This implementation will contains all the emoji that are provided on the site [1].
Currently, 16 emojis have been added to demonstrate the functionality (on Mar 7 2023).

Based on the concepts of the emojicpp [2].

## Inclusion in CMake project

### Adding as submodule

    git submodule add https://github.com/gleb-kun/ASEmoji.git
    
### Inclusion

CMakeLists.txt:

    add_subdirectory(ASEmoji)
    target_link_libraries(${PROJECT_NAME} ASEmoji)

Some cpp file:
    
    #iclude <ASEmoji.h>
    
## Sample
 
 
## Links
 
 [1] Full Emoji List, v15.0. https://unicode.org/emoji/charts/full-emoji-list.html <br />
 [2] GitHub. 99x/emojicpp. https://github.com/99x/emojicpp
 