import re as regex

def parse_emoji_test(file_path):
    emoji_data = []

    with open(file_path, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line or line.startswith("#"):
                continue

            pattern = r"([0-9A-F ]+);\s+([^#]+)#\s+(.+?)\s+E(\d+\.\d+)\s+(.+)"
            match = regex.match(pattern, line)
            if match:
                codepoints, status, emoji, version, name = match.groups()
                byte_array = [int(cp, 16) for cp in codepoints.split()]

                emoji_data.append({
                    "bytes": byte_array,
                    "type": status.strip(),
                    "version": version,
                    "name": name
                })

    return emoji_data
