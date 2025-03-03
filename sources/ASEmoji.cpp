#include "ASEmoji.h"

std::string AS::Emoji::getEmojiByName(const std::string& name)
{
    std::string key = toLowerCase(name);
    key = removeDelimiters(key);

    const std::vector<unsigned char> utf8Vector = EmojiData::getEmojiByKey(key);
    if (!utf8Vector.empty())
    {
        return toStringFromUtf8Vector(utf8Vector);
    }

    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::emojize(const std::string& input, const bool escape)
{
    std::string result;
    std::string currentToken;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (escape && i + 1 < input.size() && input[i] == '\\' && input[i + 1] == ':')
        {
            if (!currentToken.empty())
            {
                result += currentToken + ":";
                currentToken.clear();
            }
            else
                result += ":";

            ++i;
        }
        else
        {
            currentToken += input[i];

            if (currentToken.front() != ':')
            {
                result += currentToken;
                currentToken.clear();
            }
        }

        if (isTokenFormatValid(currentToken))
        {
            std::string emoji = getEmojiByName(currentToken);
            if (emoji != EMOJI_ERROR_MESSAGE)
            {
                result += emoji;
                currentToken.clear();
            }
            else
            {
                currentToken.pop_back();
                result += currentToken;
                currentToken = ":";
            }
        }
    }

    if (!currentToken.empty())
        result += currentToken;

    return result;
}

std::string AS::Emoji::toLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return string;
}

std::string AS::Emoji::removeDelimiters(std::string string)
{
    string.erase(std::remove_if(string.begin(), string.end(), [](const char c) {
        return c == ' ' || c == '\t' || c == ':' || c == '_' || c == '-' || c == '&' || c == '.';
    }), string.end());

    return string;
}

std::string AS::Emoji::toStringFromUtf8Vector(const std::vector<unsigned char>& vector)
{
    std::string str(reinterpret_cast<const char*>(vector.data()), vector.size());
    return str;
}

bool AS::Emoji::isTokenFormatValid(const std::string& token)
{
    if (token.size() <= 2)
        return false;

    return token.front() == ':' && token.back() == ':';
}
