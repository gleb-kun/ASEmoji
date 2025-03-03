import sys
import re
from parse_emoji_test import parse_emoji_test

def create_key_name(name):
    return re.sub(r"[ \-:,&.]", "", name.lower())

def numbers_to_hex_string(numbers):
    hex_bytes = []

    for number in numbers:
        emoji = chr(number)
        utf8_bytes = emoji.encode('utf-8')
        hex_bytes.extend(utf8_bytes)

    length = len(hex_bytes)

    if length > 18:
        for n in range(5, 1, -1):
            if length % n == 0:
                parts = n
                break
        else:
            parts = 2

        chunk_size = length // parts
        chunks = [hex_bytes[i:i + chunk_size] for i in range(0, length, chunk_size)]

        chunk_strings = [", ".join(f"0x{byte:02X}" for byte in chunk) for chunk in chunks]
        bytes_matrix_str = ",\n\t\t".join(chunk_strings)
    else:
        bytes_matrix_str = ", ".join(f"0x{byte:02X}" for byte in hex_bytes)

    hex_string = f"\t{{\n\t\t{bytes_matrix_str},\n\t}}}},"
    return hex_string

def update_cpp(emoji_data, cpp_file):
    start_marker_pattern = r"std::unordered_map<std::string, std::vector<unsigned char>> AS::\w+::mEmojiMapByName = {"
    end_marker = "};"

    with open(cpp_file, "r", encoding="utf-8") as file:
        lines = file.readlines()

    start_index = -1
    for i, line in enumerate(lines):
        if re.search(start_marker_pattern, line):
            start_index = i + 1
            break

    end_index = -1
    for i, line in enumerate(lines[start_index:], start=start_index):
        if end_marker in line:
            end_index = i
            break

    new_entries = []
    idx = 1
    for emoji in emoji_data:
        if emoji["type"] == "fully-qualified":
            key = create_key_name(emoji["name"])
            hex_string = numbers_to_hex_string(emoji["bytes"])
            comment = f"// {idx}\t// {emoji['name']}"
            entries_line = f"\t{comment}\n\t{{\"{key}\",\n{hex_string}\n\n"
            new_entries.append(entries_line)

            idx += 1

    lines[start_index:end_index] = ["\n"] + new_entries

    with open(cpp_file, "w", encoding="utf-8") as file:
        file.writelines(lines)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python update_cpp.py <emoji_data_file> <cpp_file>")
        sys.exit(1)

    emoji_data_file = sys.argv[1]
    cpp_file = sys.argv[2]
    emoji_data = parse_emoji_test(emoji_data_file)
    update_cpp(emoji_data, cpp_file)
    sys.exit(0)
