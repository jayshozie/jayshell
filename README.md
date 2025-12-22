# 💻 jayshell - A Learner's Command-Line Shell in C

`jayshell` is a simple command-line shell implemented in C, designed as a
learning exercise. It supports basic command execution, pipelining, and
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
- **Compiling the Jayshell:** There is a Makefile in the root of the repository.
You should be able to just call `make release` in the root of the repository.
```bash
~/jayshell $ make release
# Don't forget to run make clean when you'll rebuild.
```
- **Running Jayshell:** After that, you can run jayshell within that repo's root
with;
```bash
~/jayshell $ ./jayshell
$ whoami
jaysh
$ ls -lAh
drwxrwxr-x 2 jaysh jaysh 4.0K Dec 22 17:54 builtins
drwxrwxr-x 8 jaysh jaysh 4.0K Dec 22 18:08 .git
-rw-rw-r-- 1 jaysh jaysh  130 Dec  9 13:34 .gitignore
drwxrwxr-x 2 jaysh jaysh 4.0K Dec 22 18:01 include
-rwxrwxr-x 1 jaysh jaysh  26K Dec 22 18:01 jayshell
-rw-rw-r-- 1 jaysh jaysh  35K Dec 12 11:53 LICENSE
-rw-rw-r-- 1 jaysh jaysh  946 Dec 22 17:29 makefile
drwxrwxr-x 2 jaysh jaysh 4.0K Dec 22 18:01 obj
-rw-rw-r-- 1 jaysh jaysh 2.6K Dec 22 18:08 README.md
drwxrwxr-x 2 jaysh jaysh 4.0K Dec 22 17:51 src
-rw-rw-r-- 1 jaysh jaysh  471 Dec 22 18:03 todo.md
# well without the GitHub's coloring of course.
$ cd builtins/
$ pwd
/home/jaysh/projects/c-mastery-projects/jayshell/builtins
$ cd -
$ pwd
/home/jaysh/projects/c-mastery-projects/jayshell
...
```

## ✅ Progress

- [ ] **🚀 v3.0 - Complex Parsing:** Implementation of pipelining, multi-command
execution, redirection, etc. will be the milestone of v3.0.

- [x] **🚀 v2.0 - Separation of Functionality:** Most of the functionality will
be separated into their respective source files, which will be the milestone of
v2.0.

- [x] **📁 `cd -` Support:** You can use `cd -` to go back to the `OLD_PWD`.

- [x] **📁 `cd ~/...` and `cd ~` Support:** Now, you can use `cd ~` and
`cd ~/...` for changing directories.

- [x] **🚀 v1.0:** The initial version of Jayshell is ready to use.
    - [x] Jayshell now supports command execution, and `exit` and `cd` commands.

## 📝 References

- **`TLPI`:** *The Linux Programming Interface, by Michael Kerrisk*

## 📄 License

This project is licensed under the GNU Public License v3.0. Please read the
[LICENSE](LICENSE) file for more information.
