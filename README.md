# AS::Emoji
AS::Emoji C++ Library

## About

:heart::fist::v:

Emoji for C++ Developers.
List of supported emoji in [EmojiList.md](EmojiList.md).
This implementation will contain all emojis presented on the [Unicode official site](https://unicode.org/emoji/charts/full-emoji-list.html) (Full Emoji List, v16.0) .
Currently, 42 emojis have been added to demonstrate the functionality (on Feb 28 2025).

This project was inspired by
[emojicpp](https://github.com/99x/emojicpp) &
[emoji](https://github.com/carpedm20/emoji)
projects.

## Usage

### 1. Installation

First of all, it is possible to install the library into the system.
This is done in the standard way:

    git clone https://github.com/gleb-kun/ASEmoji.git
    cd ASEmoji
    make
    sudo make install

In this case, the library will be installed in the standard system directories:
header files in `/usr/local/include/ASEmoji`,
static library in `/usr/local/lib`,
and CMake configuration files in `/usr/local/lib/cmake/ASEmoji`.

#### Sample

In this case, after installation, you can specify the next target in the `CMakeLists.txt`:

```CMake
find_package(ASEmoji REQUIRED)
target_link_libraries(${PROJECT_NAME} ASEmoji::ASEmoji)
```

Then you can use the library as follows:

```C++
#include <iostream>
#include <ASEmoji/ASEmoji.h>

int main()
{
    std::cout << "Hello, World! " + AS::Emoji::getUtf8StringByName("Grinning Face with Smiling Eyes") << std::endl;
    std::cout << AS::Emoji::emojize("Hello, World! :Grinning Face with Smiling Eyes:") << std::endl;
    return 0;
}
```

### 1. Inclusion in project as git submodule

You can use this library as a git submodule. A submodule is connected in your project directory:

    git submodule add https://github.com/gleb-kun/ASEmoji.git

To include **AS::Emoji** in your project via CMake, add the following lines to your `CMakeLists.txt`:

```CMake
add_subdirectory(ASEmoji)
target_link_libraries(${PROJECT_NAME} ASEmoji)
```

In this case, the `ASEmoji` subdirectory was placed to the root folder of the project.
Accordingly, in this case, you can use the library as follows:

```C++
#include <iostream>
#include <ASEmoji.h>

int main()
{
    std::cout << "Hello, World! " + AS::Emoji::getUtf8StringByName("Grinning Face with Smiling Eyes") << std::endl;
    std::cout << AS::Emoji::emojize("Hello, World! :Grinning Face with Smiling Eyes:") << std::endl;
    return 0;
}
```

## Additional information

The name of the library, namely the "AS" part, is an abbreviation for Additional Software.

## Links
 
 [1] Full Emoji List, v15.0. URL: https://unicode.org/emoji/charts/full-emoji-list.html.<br />
 [2] GitHub. 99x/emojicpp. URL: https://github.com/99x/emojicpp.
 [3] GitHub. carpedm20/emoji. URL: https://github.com/carpedm20/emoji.
 