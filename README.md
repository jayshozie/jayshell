# 💻 jayshell

`jayshell` is a simple command-line shell implemented in C, designed as a
learning exercise for myself. It only supports basic command execution and a few
built-ins, for now ;).

## 🚀 Features

* Modular File Structure for Easier Expansion
* `exit` (with exit codes)
* `cd` (including `cd - `)
* `pwd`
* `~` Expansion

## 🛠️ Requirements

As **jayshell** evolves through its milestones named after Computer Science
pioneers, the dependencies and requirements will scale accordingly.

### 🏗️ Core Requirements (v1.0 - v5.0)

* **💻 Operating System:** POSIX-compliant OS (Linux, macOS, BSD)
* **🔨 Compiler:** `gcc` with support for the C11 standard (`clang` supt. soon)
* **📦 Build Tools:** `GNU Make`
* **📚 Libraries:** `libreadline` for the shell prompt, interactive command
history and editing features

### 🧬 Advanced Requirements (v6.0+)

* **🔍 Lexer Generator:** `Flex` (Fast Lexical Analyzer)
* **📐 Parser Generator:** `Bison` (GNU Parser Generator)

### 🎨 Optional for UI/UX (v5.0+)

* **🔡 [Nerd Font](https://www.nerdfonts.com/):** A **Nerd Font** is required to
correctly display icons in the git integration and dynamic prompt.

## 📦 Installation

- **Cloning the Repository**: First, clone the repository to your machine.
```bash
~ $ git clone git@github.com:jayshozie/jayshell.git
~ $ cd jayshell
~/jayshell $
```

- **Compiling the Jayshell:** There is a Makefile at the root of the repository.
You should be able to just call `make release` in the root of the repository.
```bash
~/jayshell $ make release
```
> [!IMPORTANT]
> Don't forget to run `make clean` before a rebuild.
> [!NOTE]
> You can use `make debug` to compile jayshell with the debugging flags.

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
/home/my_user/jayshell/builtins
$ cd -
$ pwd
/home/my_user/jayshell
...
```

## ✅ Progress

- [x] **🥚 v1.0 - *Neumann*:** The initial implementation of Jayshell. It has an
loop, uses `strtok` for parsing, has basic support for external commands using
`fork` and `execvp`. It has 2 builtins: `cd` and `exit`. `cd` defaults to home
when no other argument is given.
    - [x] **🐣 v1.5 - *Neumann+*:** Added `cd -` and `cd ~` path expansions.

- [x] **🏺 v2.0 - *Babbage*:** Complete refactor into modular directories
`src/`, `builtins/`, and `include/`, with the parser and tilde expander
separated from the built-in `cd` command.
    - [x] **🐞 v2.5 - *Hopper*:** Fixing the environment initialization bug;
    rewrite `cd` and `pwd` symlink logic to distinguish between logical paths
    and physical paths; and error handling (needed more descriptive error
    messages)

- [x] **🔌 v3.0 - *Ritchie*:** Redirection, pipelining, logical execution, and
logical path tracking
    - [ ] **🕹️ v3.5 - *Thompson*:** Signal handling (`SIGINT`, `SIGTSTP`,
    `SIGQUIT`), and job control (`echo`, `export`, `unset`, `env`, `jobs`, `&`,
    `fg`, `bg`, `kill`, `history`)

- [ ] **📜 v4.0 - *Lovelace*:** Startup files (`.jayshellrc`,
`.jayshell_aliasias`), shebang support, dynamic prompt (git status indicator,
and cwd), and new built-ins (`source`, `alias` / `unalias`, `type`, `read`,
`wait`)

- [ ] **🧬 v5.0 - *Backus*:** Lexer/Parser rewrite using Bison/Flex, expansion
engine (quote handling `'`, `"`; escape characters `\`; command substitution
`$(command)`; globbing `*`, `?`), and new built-ins (`printf`, `hash`)

- [ ] **🧠 v6.0 - *Turing*:** Control flow (conditionals, logic, loops), data
types (`int`, `float`, `double`), and arithmetic operations

## 📝 References

- **`TLPI`:** *The Linux Programming Interface, by Michael Kerrisk*

## 🤝 Contributing

You're more than welcome to open a pull request or an issue.

If you're planning to open a PR, please check the
[CONTRIBUTING.md](CONTRIBUTING.md) file located at the root of the repository.

## 📄 License

This project is licensed under the GNU Public License v3.0. Please read the
[LICENSE](LICENSE) file for more information.
