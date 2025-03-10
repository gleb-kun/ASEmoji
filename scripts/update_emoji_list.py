import subprocess

emoji_data_file = "emoji-test.txt"

script_md = "update_md.py"
md_file = "../EmojiList.md"

script_cpp = "update_cpp.py"
cpp_file = "../sources/EmojiData.cpp"

subprocess.run(["python", script_md, emoji_data_file, md_file])
subprocess.run(["python", script_cpp, emoji_data_file, cpp_file])
