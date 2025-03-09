#include "ASEmoji.h"

std::string AS::Emoji::getEmojiByName(const std::string& name)
{
    const std::string key = createKey(name);

    const std::vector<unsigned char> utf8Vector = EmojiData::getEmojiByKey(key);
    if (!utf8Vector.empty() && isValidUtf8(utf8Vector))
        return toStringFromUtf8Vector(utf8Vector);

    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::getEmojiByUtf8(const std::vector<unsigned char>& bytes)
{
    if (!bytes.empty() && isValidUtf8(bytes))
        return toStringFromUtf8Vector(bytes);
    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::getEmojiByUtf16(const std::vector<char16_t>& bytes)
{
    if (!bytes.empty() && isValidUtf16(bytes))
        return toStringFromUtf16Vector(bytes);
    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::getEmojiByUtf32(const std::vector<char32_t>& bytes)
{
    if (!bytes.empty() && isValidUtf32(bytes))
        return toStringFromUtf32Vector(bytes);
    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::emojize(const std::string& input, const bool escape)
{
    std::string result;
    std::string currentToken;

    for (size_t i = 0; i < input.size(); i++)
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

            i++;
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

std::string AS::Emoji::createKey(const std::string& string)
{
    const std::string key = toLowerCase(string);
    return removeDelimiters(key);
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
    if (!vector.empty() && isValidUtf8(vector))
    {
        std::string str(reinterpret_cast<const char*>(vector.data()), vector.size());
        return str;
    }
    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::toStringFromUtf16Vector(const std::vector<char16_t>& vector)
{
    if (!vector.empty() && isValidUtf16(vector))
    {
        const std::u16string utf16String(vector.begin(), vector.end());
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        return convert.to_bytes(utf16String);
    }
    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::toStringFromUtf32Vector(const std::vector<char32_t>& vector)
{
    if (!vector.empty() && isValidUtf32(vector))
    {
        const std::u32string utf32String(vector.begin(), vector.end());
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(utf32String);
    }
    return EMOJI_ERROR_MESSAGE;
}

bool AS::Emoji::isValidUtf8(const std::vector<unsigned char>& vector)
{
    size_t i = 0;
    while (i < vector.size())
    {
        const unsigned char byte = vector[i];
        int numBytes = 0;

        if ((byte & 0x80) == 0)
            numBytes = 1;
        else if ((byte & 0xE0) == 0xC0)
            numBytes = 2;
        else if ((byte & 0xF0) == 0xE0)
            numBytes = 3;
        else if ((byte & 0xF8) == 0xF0)
            numBytes = 4;
        else
            return false;

        if (i + numBytes > vector.size())
            return false;

        for (int j = 1; j < numBytes; j++)
        {
            if ((vector[i + j] & 0xC0) != 0x80)
                return false;
        }

        char32_t codepoint = 0;
        if (numBytes == 2)
        {
            codepoint = ((vector[i] & 0x1F) << 6) | (vector[i + 1] & 0x3F);
            if (codepoint < 0x80)
                return false;
        }
        else if (numBytes == 3)
        {
            codepoint = ((vector[i] & 0x0F) << 12) | ((vector[i + 1] & 0x3F) << 6) | (vector[i + 2] & 0x3F);
            if (codepoint < 0x800 || (codepoint >= 0xD800 && codepoint <= 0xDFFF))
                return false;
        }
        else if (numBytes == 4)
        {
            codepoint = ((vector[i] & 0x07) << 18) | ((vector[i + 1] & 0x3F) << 12) |
                        ((vector[i + 2] & 0x3F) << 6) | (vector[i + 3] & 0x3F);
            if (codepoint < 0x10000 || codepoint > 0x10FFFF)
                return false;
        }

        i += numBytes;
    }
    return true;
}

bool AS::Emoji::isValidUtf16(const std::vector<char16_t>& vector)
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        const char16_t ch = vector[i];

        if (ch >= 0xD800 && ch <= 0xDBFF)
        {
            if (i + 1 >= vector.size() || vector[i + 1] < 0xDC00 || vector[i + 1] > 0xDFFF)
                return false;
            i++;
        }
        else if (ch >= 0xDC00 && ch <= 0xDFFF)
            return false;
    }
    return true;
}

bool AS::Emoji::isValidUtf32(const std::vector<char32_t>& vector)
{
    for (const char32_t ch : vector)
    {
        if (ch >= 0xD800 && ch <= 0xDFFF)
            return false;
        if (ch > 0x10FFFF)
            return false;
    }
    return true;
}

bool AS::Emoji::isTokenFormatValid(const std::string& token)
{
    if (token.size() <= 2)
        return false;

    return token.front() == ':' && token.back() == ':';
}
