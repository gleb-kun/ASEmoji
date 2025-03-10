# AS::Emoji
AS::Emoji C++ Library

## About

:heart::fist::v:

Emoji for C++ Developers.
List of supported emoji in [EmojiList.md](EmojiList.md). There are currently 3781 emoji supported in the library (Last updated March 3, 2025).
This implementation contains all emojis presented on the [official Unicode website](https://unicode.org/emoji/charts/full-emoji-list.html) (Full Emoji List, v16.0).
In addition, the library supports emojis based on skin color, gender, etc., as well as combinations.
As a result, all _fully-qualified_ emojis presented in the [document](https://unicode.org/Public/emoji/latest/emoji-test.txt) are supported.

This project was inspired by
[emojicpp](https://github.com/99x/emojicpp) &
[emoji](https://github.com/carpedm20/emoji)
projects.

## Usage

### 1. Installation

First of all, it is possible to install the library into the system.
This is done in the standard way:

```shell
git clone https://github.com/gleb-kun/ASEmoji.git
cd ASEmoji
make
sudo make install
```

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
    std::cout << "Hello, World! " + AS::Emoji::getEmojiByName("Grinning Face with Smiling Eyes") << std::endl;
    std::cout << AS::Emoji::emojize("Hello, World! :Grinning Face with Smiling Eyes:") << std::endl;
    return 0;
}
```

### 2. Inclusion in project as git submodule

You can also use this library as a git submodule. A submodule is connected in your project directory:

```shell
git submodule add https://github.com/gleb-kun/ASEmoji.git
```

To include **AS::Emoji** in your project via CMake, add the following lines to your `CMakeLists.txt`:

```CMake
add_subdirectory(ASEmoji)
target_link_libraries(${PROJECT_NAME} ASEmoji)
```

In this case, the `ASEmoji` subdirectory was placed to the root folder of your project.
Accordingly, in this case, you can use the library as follows:

```C++
#include <iostream>
#include <ASEmoji.h>

int main()
{
    std::cout << "Hello, World! " + AS::Emoji::getEmojiByName("Grinning Face with Smiling Eyes") << std::endl;
    std::cout << AS::Emoji::emojize("Hello, World! :Grinning Face with Smiling Eyes:") << std::endl;
    return 0;
}
```

## Develop

### Main information

The development of the **AS::Emoji** library has just begun.
Only the first version has been released, so many features may not work as intended.
If you encounter a problem/have any wishes/questions,
we will be glad to receive your post in [Issues](https://github.com/gleb-kun/ASEmoji/issues).
In the future, the developers strive to include all the features from similar libraries. The authors will be grateful for any contribution to the development.
PR? Welcome! :blush::+1:

### Additional information

The name of the library, namely the "AS" part, is an abbreviation for Additional Software.

## Links
 
 [1] UNICODE. Full Emoji List, v16.0. URL: https://unicode.org/emoji/charts/full-emoji-list.html.<br/>
 [2] UNICODE. emoji-test.txt the document. URL: https://unicode.org/Public/emoji/latest/emoji-test.txt.<br/>
 [3] GitHub. 99x/emojicpp. URL: https://github.com/99x/emojicpp.<br/>
 [4] GitHub. carpedm20/emoji. URL: https://github.com/carpedm20/emoji.
 