#ifndef EMOJIDATA_CPP_H
#define EMOJIDATA_CPP_H

#include <unordered_map>
#include <string>
#include <vector>

namespace AS
{
    class EmojiData
    {
        public:
            static std::vector<unsigned char> getEmojiByKey(const std::string& name);
            static void addStr()
            {
                value += " dsa";
            }

        private:
            static std::string value;
            static std::unordered_map<std::string, std::vector<unsigned char>> mEmojiMapByName;
    };
}

#endif //EMOJIDATA_CPP_H
