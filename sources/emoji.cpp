#include "emoji.h"

std::string AS::Emoji::getUtf8StringByName(const std::string& name)
{
    std::string key = toLowerCase(name);
    key.erase(remove_if(key.begin(), key.end(), isspace), key.end());

    if (mEmojiMapByName.count(key))
    {
        std::vector<char32_t> utf8Vector = mEmojiMapByName.find(key)->second;
        if (!utf8Vector.empty())
        {
            return toHexStringFromUtf8Vector(utf8Vector);
        }
    }

    return EMOJI_ERROR_MESSAGE;
}

std::string AS::Emoji::toLowerCase(std::string string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return string;
}

std::string AS::Emoji::toHexString(const char* data, unsigned int len)
{
    std::string result;
    for (int j = (int) len - 1; j >=0; j--)
    {
        result += data[j];
    }
    return result;
}

std::string AS::Emoji::toHexStringFromUtf8Vector(std::vector<char32_t> vector)
{
    unsigned int size = vector.size();
    char utf8[4];
    std::string utf8String;

    for (unsigned int i = 0; i < size; i++)
    {
        memcpy(utf8, &vector.at(i), sizeof(char32_t));
        utf8String += toHexString(utf8, 4);
    }

    return utf8String;
}

std::map<std::string, std::vector<char32_t>> AS::Emoji::mEmojiMapByName = {
        {"grinningface",                                    {0xF09F9880}},                                          // 1    // grinning face
        {"grinningfacewithbigeyes",                         {0xF09F9883}},                                          // 2    // grinning face with big eyes
        {"grinningfacewithsmilingeyes",                     {0xF09F9884}},                                          // 3    // grinning face with smiling eyes
        {"faceinclouds",                                    {0x0000F09F, 0x98B6E280, 0x8DF09F8C, 0xABEFB88F}},      // 43   // face in clouds
        {"speechballoon",                                   {0xF09F92AC}},                                          // 161  // speech balloon
        {"handshake",                                       {0xF09FA49D}},                                          // 205  // handshake
        {"speakinghead",                                    {0xF09F97A3}},                                          // 525  // speaking head
        {"graduationcap",                                   {0xF09F8E93}},                                          // 1161 // graduation cap
        {"pagefacingup",                                    {0xF09F9384}},                                          // 1245 // page facing up
        {"moneybag",                                        {0xF09F92B0}},                                          // 1251 // money bag
        {"spiralnotepad",                                   {0xF09F9792}},                                          // 1287 // spiral notepad
        {"chartincreasing",                                 {0xF09F9388}},                                          // 1290 // chart increasing
        {"chartdecreasing",                                 {0xF09F9389}},                                          // 1291 // chart decreasing
        {"gear",                                            {0xE29A99}},                                            // 1325 // gear
        {"leftarrowcurvingright",                           {0xE286AA}},                                            // 1420 // left arrow curving right
        {"plus",                                            {0x00E29E95}},                                          // 1485 // plus
        {"currencyexchange",                                {0xF09F92B1}},                                          // 1497 // currency exchange
        {"flag:unitedkingdom",                              {0xF09F87AC, 0xF09F87A7}},                              // 1695 // flag: United Kingdom
        {"flag:russia",                                     {0xF09F87B7, 0xF09F87BA}},                              // 1810 // flag: Russia
};

std::map<std::vector<char32_t>, std::vector<char32_t>> AS::Emoji::mEmojiMapByUtf32 = {
        {{0x0001F600},                                      {0xF09F9880}},                                          // 1    // grinning face
        {{0x0001F603},                                      {0xF09F9883}},                                          // 2    // grinning face with big eyes
        {{0x0001F604},                                      {0xF09F9884}},                                          // 3    // grinning face with smiling eyes
        {{0x0001F636, 0x0000200D, 0x0001F32B, 0x0000FE0F},  {0x0000F09F, 0x98B6E280, 0x8DF09F8C, 0xABEFB88F}},      // 43   // face in clouds
        {{0x0001F4AC},                                      {0xF09F92AC}},                                          // 161  // speech balloon
        {{0x0001F91D},                                      {0xF09FA49D}},                                          // 205  // handshake
        {{0x0001F5E3},                                      {0xF09F97A3}},                                          // 525  // speaking head
        {{0x0001F393},                                      {0xF09F8E93}},                                          // 1161 // graduation cap
        {{0x0001F4C4},                                      {0xF09F9384}},                                          // 1245 // page facing up
        {{0x0001F4B0},                                      {0xF09F92B0}},                                          // 1251 // money bag
        {{0x0001F5D2},                                      {0xF09F9792}},                                          // 1287 // spiral notepad
        {{0x0001F4C8},                                      {0xF09F9388}},                                          // 1290 // chart increasing
        {{0x0001F4C9},                                      {0xF09F9389}},                                          // 1291 // chart decreasing
        {{0x00002699},                                      {0xE29A99}},                                            // 1325 // gear
        {{0x000021AA},                                      {0xE286AA}},                                            // 1420 // left arrow curving right
        {{0x00002795},                                      {0x00E29E95}},                                          // 1485 // plus
        {{0x0001F4B1},                                      {0xF09F92B1}},                                          // 1497 // currency exchange
        {{0x0001F1EC, 0x0001F1E7},                          {0xF09F87AC, 0xF09F87A7}},                              // 1695 // flag: United Kingdom
        {{0x0001F1F7, 0x0001F1FA},                          {0xF09F87B7, 0xF09F87BA}},                              // 1810 // flag: Russia
};
