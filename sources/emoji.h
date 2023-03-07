#ifndef ASEMOJI_EMOJI_H
#define ASEMOJI_EMOJI_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <ios>
#include <iostream>

#define EMOJI_ERROR_MESSAGE "AS::Emoji(?)"

namespace AS
{
    class Emoji
    {
    public:
        static std::string getUtf8StringByName(const std::string& name);

//        static std::string getUtf8StringByUtf32(char32_t value);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2, char32_t v3);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2, char32_t v3, char32_t v4);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5, char32_t v6);
//        static std::string getUtf8StringByUtf32(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5, char32_t v6, char32_t v7);
//        static std::string getUtf8StringByUtf32(std::vector<char32_t> values);
//
//        static std::string getUtf8StringByUtf8(char32_t value);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2, char32_t v3);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2, char32_t v3, char32_t v4);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5, char32_t v6);
//        static std::string getUtf8StringByUtf8(char32_t v1, char32_t v2, char32_t v3, char32_t v4, char32_t v5, char32_t v6, char32_t v7);
//        static std::string getUtf8StringByUtf8(std::vector<char32_t> values);

    private:
        static std::string toLowerCase(std::string string);
        static std::string toHexString(const char* data, unsigned int len);
        static std::string toHexStringFromUtf8Vector(std::vector<char32_t> vector);

    private:
        static std::map<std::string, std::vector<char32_t>> mEmojiMapByName;
        static std::map<std::vector<char32_t>, std::vector<char32_t>> mEmojiMapByUtf32;
    };
}

#endif //ASEMOJI_EMOJI_H
