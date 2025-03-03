import sys
import re
from parse_emoji_test import parse_emoji_test

def create_key_name(name):
    name = re.sub(r"[-]", " ", name)
    name = re.sub(r"[:,&.]", "", name)
    return name

def numbers_to_unicode_format(numbers):
    return " ".join(f"U+{num:X}" for num in numbers)

def bytes_to_emoji(bytes_list):
    emoji = ''.join(chr(byte) for byte in bytes_list)
    return emoji

def update_md(emoji_data, md_file):
    with open(md_file, "w", encoding="utf-8") as file:
        file.write("| #\t| Display | Name in AS::Emoji | CLDR Name | Code |\n")
        file.write("|----|---------|-------------------|-----------|------|\n")

        idx = 1
        for emoji in emoji_data:
            if emoji["type"] == "fully-qualified":
                key = create_key_name(emoji["name"])
                cldr_name = emoji["name"]
                code = numbers_to_unicode_format(emoji["bytes"])
                display = bytes_to_emoji(emoji["bytes"])

                file.write(f"| {idx}\t| {display}| {key} | {cldr_name} | {code} |\n")
                idx += 1

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python update_cpp.py <emoji_data_file> <md_file>")
        sys.exit(1)

    emoji_data_file = sys.argv[1]
    md_file = sys.argv[2]
    emoji_data = parse_emoji_test(emoji_data_file)
    update_md(emoji_data, md_file)
    sys.exit(0)
