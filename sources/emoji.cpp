#include "emoji.h"

std::string AS::Emoji::getEmojiByName(const std::string& name)
{
    std::string key = toLowerCase(name);
    key = removeDelimiters(key);

    if (mEmojiMapByName.count(key))
    {
        const std::vector<unsigned char> utf8Vector = mEmojiMapByName.find(key)->second;
        if (!utf8Vector.empty())
        {
            return toStringFromUtf8Vector(utf8Vector);
        }
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
        return c == ' ' || c == '\t' || c == ':' || c == '_' || c == '-';
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

std::unordered_map<std::string, std::vector<unsigned char>> AS::Emoji::mEmojiMapByName = {
    {"grinningface",                {0xF0, 0x9F, 0x98, 0x80}},                                                              // 1    // grinning face
    {"grinningfacewithbigeyes",     {0xF0, 0x9F, 0x98, 0x83}},                                                              // 2    // grinning face with big eyes
    {"grinningfacewithsmilingeyes", {0xF0, 0x9F, 0x98, 0x84}},                                                              // 3    // grinning face with smiling eyes
    {"faceinclouds",                {0xF0, 0x9F, 0x98, 0xB6, 0xE2, 0x80, 0x8D, 0xF0, 0x9F, 0x8C, 0xAB, 0xEF, 0xB8, 0x8F}},  // 43   // face in clouds
    {"speechballoon",               {0xF0, 0x9F, 0x92, 0xAC}},                                                              // 161  // speech balloon
    {"handshake",                   {0xF0, 0x9F, 0xA4, 0x9D}},                                                              // 205  // handshake
    {"speakinghead",                {0xF0, 0x9F, 0x97, 0xA3}},                                                              // 525  // speaking head
    {"soccerball",                  {0x00, 0xE2, 0x9A, 0xBD}},                                                              // 1095 // soccer ball
    {"videogame",                   {0xF0, 0x9F, 0x8E, 0xAE}},                                                              // 1129 // video game
    {"slotmachine",                 {0xF0, 0x9F, 0x8E, 0xB0}},                                                              // 1131 // slot machine
    {"gamedie",                     {0xF0, 0x9F, 0x8E, 0xB2}},                                                              // 1132 // game die
    {"graduationcap",               {0xF0, 0x9F, 0x8E, 0x93}},                                                              // 1161 // graduation cap
    {"pagefacingup",                {0xF0, 0x9F, 0x93, 0x84}},                                                              // 1245 // page facing up
    {"moneybag",                    {0xF0, 0x9F, 0x92, 0xB0}},                                                              // 1251 // money bag
    {"spiralnotepad",               {0xF0, 0x9F, 0x97, 0x92}},                                                              // 1287 // spiral notepad
    {"chartincreasing",             {0xF0, 0x9F, 0x93, 0x88}},                                                              // 1290 // chart increasing
    {"chartdecreasing",             {0xF0, 0x9F, 0x93, 0x89}},                                                              // 1291 // chart decreasing
    {"outboxtray",                  {0xF0, 0x9F, 0x93, 0xA4}},                                                              // 1297 // outbox tray
    {"inboxtray",                   {0xF0, 0x9F, 0x93, 0xA5}},                                                              // 1298 // inbox tray
    {"gear",                        {0xE2, 0x9A, 0x99}},                                                                    // 1325 // gear
    {"pushpin",                     {0xF0, 0x9F, 0x93, 0x8D}},                                                              // 1326 // pushpin
    {"paperclip",                   {0xF0, 0x9F, 0x93, 0x8E}},                                                              // 1328 // paperclip
    {"identificationcard",          {0xF0, 0x9F, 0xAA, 0xAA}},                                                              // 1416 // identification card
    {"leftarrowcurvingright",       {0xE2, 0x86, 0xAA}},                                                                    // 1420 // left arrow curving right
    {"plus",                        {0x00, 0xE2, 0x9E, 0x95}},                                                              // 1485 // plus
    {"currencyexchange",            {0xF0, 0x9F, 0x92, 0xB1}},                                                              // 1497 // currency exchange
    {"flagarmenia",                 {0xF0, 0x9F, 0x87, 0xA6, 0xF0, 0x9F, 0x87, 0xB2}},                                      // 1621 // flag: Armenia
    {"flagazerbaijan",              {0xF0, 0x9F, 0x87, 0xA6, 0xF0, 0x9F, 0x87, 0xBF}},                                      // 1630 // flag: Azerbaijan
    {"flagswitzerland",             {0xF0, 0x9F, 0x87, 0xA8, 0xF0, 0x9F, 0x87, 0xAD}},                                      // 1657 // flag: Switzerland
    {"flaggermany",                 {0xF0, 0x9F, 0x87, 0xA9, 0xF0, 0x9F, 0x87, 0xAA}},                                      // 1672 // flag: Germany
    {"flagspain",                   {0xF0, 0x9F, 0x87, 0xAA, 0xF0, 0x9F, 0x87, 0xB8}},                                      // 1685 // flag: Spain
    {"flagfrance",                  {0xF0, 0x9F, 0x87, 0xAB, 0xF0, 0x9F, 0x87, 0xB7}},                                      // 1693 // flag: France
    {"flagunitedkingdom",           {0xF0, 0x9F, 0x87, 0xAC, 0xF0, 0x9F, 0x87, 0xA7}},                                      // 1695 // flag: United Kingdom
    {"flaggeorgia",                 {0xF0, 0x9F, 0x87, 0xAC, 0xF0, 0x9F, 0x87, 0xAA}},                                      // 1697 // flag: Georgia
    {"flagitaly",                   {0xF0, 0x9F, 0x87, 0xAE, 0xF0, 0x9F, 0x87, 0xB9}},                                      // 1729 // flag: Italy
    {"flagkyrgyzstan",              {0xF0, 0x9F, 0x87, 0xB0, 0xF0, 0x9F, 0x87, 0xAC}},                                      // 1735 // flag: Kyrgyzstan
    {"flagromania",                 {0xF0, 0x9F, 0x87, 0xB7, 0xF0, 0x9F, 0x87, 0xB4}},                                      // 1808 // flag: Romania
    {"flagrussia",                  {0xF0, 0x9F, 0x87, 0xB7, 0xF0, 0x9F, 0x87, 0xBA}},                                      // 1810 // flag: Russia
    {"flagtajikistan",              {0xF0, 0x9F, 0x87, 0xB9, 0xF0, 0x9F, 0x87, 0xAF}},                                      // 1839 // flag: Tajikistan
    {"flagturkey",                  {0xF0, 0x9F, 0x87, 0xB9, 0xF0, 0x9F, 0x87, 0xB7}},                                      // 1845 // flag: Turkey
    {"flagukraine",                 {0xF0, 0x9F, 0x87, 0xBA, 0xF0, 0x9F, 0x87, 0xA6}},                                      // 1850 // flag: Ukraine
    {"flaguzbekistan",              {0xF0, 0x9F, 0x87, 0xBA, 0xF0, 0x9F, 0x87, 0xBF}},                                      // 1856 // flag: Uzbekistan
};
