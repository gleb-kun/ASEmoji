#ifndef ASEMOJI_EMOJI_H
#define ASEMOJI_EMOJI_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define EMOJI_ERROR_MESSAGE "AS::Emoji(?)"

namespace AS
{
    class Emoji
    {
        public:
            static std::string getEmojiByName(const std::string& name);

        private:
            static std::string toLowerCase(std::string string);
            static std::string removeDelimiters(std::string string);
            static std::string toStringFromUtf8Vector(const std::vector<unsigned char>& vector);

        private:
            static std::unordered_map<std::string, std::vector<unsigned char>> mEmojiMapByName;
    };
}

#endif //ASEMOJI_EMOJI_H
