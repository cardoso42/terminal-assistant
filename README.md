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

You need the following libraries:

- [libcurl](https://curl.se/libcurl/) - For making HTTP requests
- clang-format - For code formatting

On Debian/Ubuntu systems, you can install them with:

```bash
sudo apt install libcurl4-openssl-dev clang-format
```

---

## ⚙️ Building with CMake

Create the directories and build:

```bash
mkdir build && cd build
cmake ..
make
```

To format all source files:

```bash
make format
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

---

## 🎨 Code Formatting

The project uses clang-format for consistent code formatting. Formatting is automatically applied to staged files when you commit changes.

### Manual Formatting

You can format all source files using CMake's format target:

```bash
cd build
make format
```

### Formatting Rules

The formatting rules are defined in `.clang-format` in the project root. The rules are based on the LLVM style with some customizations.
