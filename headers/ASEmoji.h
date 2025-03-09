#ifndef ASEMOJI_EMOJI_H
#define ASEMOJI_EMOJI_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <codecvt>
#include <locale>

#include "EmojiData.h"

#define EMOJI_ERROR_MESSAGE "AS::Emoji(?)"

namespace AS
{
    class Emoji
    {
        public:
            static std::string getEmojiByName(const std::string& name);
            static std::string getEmojiByUtf8(const std::vector<unsigned char>& bytes);
            static std::string getEmojiByUtf16(const std::vector<char16_t>& bytes);
            static std::string getEmojiByUtf32(const std::vector<char32_t>& bytes);

            static std::string emojize(const std::string& input, bool escape = true);

        private:
            static std::string createKey(const std::string& string);
            static std::string toLowerCase(std::string string);
            static std::string removeDelimiters(std::string string);

            static std::string toStringFromUtf8Vector(const std::vector<unsigned char>& vector);
            static std::string toStringFromUtf16Vector(const std::vector<char16_t>& vector);
            static std::string toStringFromUtf32Vector(const std::vector<char32_t>& vector);

            static bool isValidUtf8(const std::vector<unsigned char>& vector);
            static bool isValidUtf16(const std::vector<char16_t>& vector);
            static bool isValidUtf32(const std::vector<char32_t>& vector);

            static bool isTokenFormatValid(const std::string& token);

        private:
            static EmojiData  mEmojiData;
    };
}

#endif //ASEMOJI_EMOJI_H
