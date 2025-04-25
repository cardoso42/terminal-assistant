# Terminal Assistant (C++)

A terminal assistant written in C++ that uses the [Deepseek API](https://deepseek.com/) to answer questions and commands with a focus on Linux terminal.

## ✅ Features

- Sends commands and questions to the Deepseek API
- Returns the response in the terminal
- Interactive execution of suggested commands
- Direct command line usage
- Currently supports Brazilian Portuguese only

---

## 📦 Dependencies

You need the following library:

- [libcurl](https://curl.se/libcurl/) - For making HTTP requests

On Debian/Ubuntu systems, you can install it with:

```bash
sudo apt install libcurl4-openssl-dev
```

---

## ⚙️ Building with CMake

Create the directories and build:

```bash
mkdir build && cd build
cmake ..
make
```

---

## 🧪 Usage

1. **Set the environment variable** with your API key:

```bash
export DEEPSEEK_API_KEY="your_key_here"
```

You can add this to your `.bashrc`, `.zshrc`, or other automatically loaded location.

2. **Run the program** with a command as an argument:

```bash
./assistant "how to list hidden files in the terminal?"
```

The program will:
- Show the assistant's response
- Ask if you want to execute the suggested command
- Execute the command if you confirm (by pressing ENTER or Y/y)
