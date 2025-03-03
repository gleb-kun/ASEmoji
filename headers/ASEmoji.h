#ifndef ASEMOJI_EMOJI_H
#define ASEMOJI_EMOJI_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "EmojiData.h"

#define EMOJI_ERROR_MESSAGE "AS::Emoji(?)"

namespace AS
{
    class Emoji
    {
        public:
            static std::string getEmojiByName(const std::string& name);
            static std::string emojize(const std::string& input, bool escape = true);

        private:
            static std::string createKey(const std::string& string);
            static std::string toLowerCase(std::string string);
            static std::string removeDelimiters(std::string string);
            static std::string toStringFromUtf8Vector(const std::vector<unsigned char>& vector);
            static bool isTokenFormatValid(const std::string& token);

        private:
            static EmojiData  mEmojiData;
    };
}

#endif //ASEMOJI_EMOJI_H
