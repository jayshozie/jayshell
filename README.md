# 💻 jayshell - A Learner's Command-Line Shell in C

`jayshell` is a simple command-line shell implemented in C, designed as a
learning exercise. It supports basic command execution, piping, and
redirection.

## 🚀 Features

- Execute simple commands with arguments
- Support for input/output redirection (`>`, `<`, `>>`)
- Support for command piping (`|`)
- Built-in commands like `cd`, `exit`, and `help`
- Error handling for invalid commands and syntax
- Signal handling for `Ctrl+C` and `Ctrl+Z`

## 📦 Installation

- **Cloning the Repository**: First, clone the repository to your machine.
```bash
~ $ git clone https://github.com/jayshozie/jayshell.git
~ $ cd jayshell
~/jayshell $
```
- **Compiling the Jayshell:** Then, you need to use your favorite compiler and
compile the `jayshell.c` source code.
```bash
~/jayshell $ gcc ./jayshell.c -o jayshell -lreadline
```
- **Running Jayshell:** After that, you can run jayshell within that repo's root
with;
```bash
~/jayshell $ ./jayshell
jaysh > whoami
jaysh # yes i named the shell after my nickname, which was not a good idea
jaysh > ls -lAh
drwxrwxr-x 8 jaysh jaysh 4.0K Dec 12 11:40 .git
-rw-rw-r-- 1 jaysh jaysh  130 Dec  9 13:34 .gitignore
-rwxrwxr-x 1 jaysh jaysh  19K Dec  9 19:42 jayshell
-rw-rw-r-- 1 jaysh jaysh 2.3K Dec 12 11:40 jayshell.c
-rw-rw-r-- 1 jaysh jaysh 1.2K Dec 12 11:45 README.md
-rw-rw-r-- 1 jaysh jaysh  190 Dec  9 19:44 todo.md
# well without the GitHub's coloring of course.
jaysh >
```

## ✅ Progress

- [x] **🚀 v1.0:** The initial version of Jayshell is ready to use.
    - [x] Jayshell now supports command execution, and `exit` and `cd` commands.

## 📝 References

- **`TLPI`:** *The Linux Programming Interface, by Michael Kerrisk*

## 📄 License

This project is licensed under the GNU Public License v3.0. Please read the
[LICENSE](LICENSE) file for more information.
