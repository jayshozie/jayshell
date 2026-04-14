# Current Status : `v3.0` New Parser and Lexer

- **Completed the new Lexer and Parser**, which was needed to allow
POSIX-compliant redirection and pipelining.

---

# TODO

## Bugs

---

# Roadmap for Jayshell

## 🕹️ v4.0 - *Thompson*

*Focus:* Stability, Signal Handling, Job Control

- [x] Switch to `<stdint.h>` integer definitions.

- [x] **Logical Execution:** Implement `&&` (AND) and `||` (OR).

- [x] **Expansion Engine - Part I:**
    - [x] *Quote Handling:* A very basic single `'` and double `"` quotes
    parser.

- [ ] **Job Control:** Support for backgrounding processes with &.

- [ ] **Variables and Simple Variable Expansion:** Add the ability for users to
set variables using the bash syntax. This requires `unset` and export to be
written as well.

- [ ] **Builtins:**
    - [ ] `echo`: With -n and -e flag support.
    - [ ] `export`: To set environment variables.
    - [ ] `unset`: To remove variables.
    - [ ] `env`: To list current environment.
    - [ ] `jobs`: List active background tasks.
    - [ ] `fg` / `bg`: Move jobs between foreground and background.
    - [ ] `kill`: Send signals to processes by PID or Job ID.

## 📜 v5.0 - *Lovelace*

*Focus:* Customization, Script Execution, Alias Logic

- [ ] **Shebang Support:** Allow execution of scripts starting with #!.

- [ ] **Signal Handling:** Correctly handle `SIGINT`, `SIGQUIT`, and `SIGTSTP`.

- [ ] **Shell-Specific Files:** Load at least .jayshellrc and .jayshell_aliases
on init, write shell commands history to ~/.jayshell_history. We will comply
with the XDG Base Directory Specification. So, the structure will be something
like:
```sh
$ ls -la "${XDG_CONFIG_HOME}/jayshell" # or ~/.config/jayshell
total ****
drwxr-xr-x *** **** *** *** ** ***** .
drwxr-xr-x *** **** *** *** ** ***** ..
-rw-r--r-- *** **** *** *** ** ***** rc
-rw-r--r-- *** **** *** *** ** ***** aliases
-rw-r--r-- *** **** *** *** ** ***** profile *
-rw-r--r-- *** **** *** *** ** ***** env     *
-rw-r--r-- *** **** *** *** ** ***** logout  *
$ ls -la "${XDG_STATE_HOME}/jayshell" # or ~/.local/state/jayshell
total **
drwxr-xr-x *** **** *** *** ** ***** .
drwxr-xr-x *** **** *** *** ** ***** ..
-rw------- *** **** *** *** ** ***** history
```
*: We may not implement these at all. I'd rather let the user decide on their
names and source them from `jayshellrc`.

- [ ] **Dynamic Prompt:**
    - [ ] *Git Integration:* Dynamic prompt with status indicators.
    - [ ] *CWD in Prompt:* Shows current working directory in prompt.

- [ ] **Built-ins:**
    - [ ] `source` / `.` : Execute scripts in the current shell context.
    - [ ] `alias` / `unalias`: Create and remove command shortcuts.
    - [ ] `type`: Identify if a command is a built-in, alias, or file.
    - [ ] `read`: Take user input into a variable.
    - [ ] `wait`: Wait for background processes to complete.
    - [ ] `history`: Integrated with ~/.jayshell_history for persistence.

## 🧬 v6.0 - *Backus*

*Focus:* Transitioning to a Formal Grammar with Flex & Bison.

- [ ] **The Lexer/Parser Rewrite:** Move away from `strtok` to a formal grammar.

- [ ] **Expansion Engine - Part II:**
    - [ ] *Quote Handling:* Fully implemented `'` and double `"` quotes parser.
    - [ ] *Escape Characters:* Support for `\`.
    - [ ] *Command Substitution:* `$(command)`.
    - [ ] *Globbing:* Wildcard expansion `*` and `?`.

- [ ] **Built-ins:**
    - [ ] `printf`: More robust output formatting.
    - [ ] `hash`: Command location caching for performance.

## 🧠 v7.0 - *Turing*

*Focus:* Turing Completeness and Data Types.

- [ ] **Control Flow:**
    - [ ] *Conditionals:* `if`, `then`, `else`, `elif`
    - [ ] *Logic:* `case`, `select`.
    - [ ] *Loops:* `for`, `while`, `until`

- [ ] **The Mathematician Update:**
    - [ ] Integer and Floating Point arithmetic.
    - [ ] *Variables types:* `int`, `float`, `double`.

- [ ] **Built-ins:**
    - [ ] `test` / `[` : For file and string comparisons.
    - [ ] `time`: Summarize system/user resource usage for a command.

---

# Done

## TODOs

- [x] **`cd` can't follow symlinks**

- [x] **Environment Initialization Bug:** Fix the bug where variables aren't
initialized on startup.

- [x] **`cd` Illegal `args[2]` Check:** Because of how the parser generates the
tokens, directly checking `args[2]` is causing weird behavior. Added a check for
`args[1]` to make sure if the command is simply `cd` and not `cd /path/to/dir`
it doesn't accidentally check an unallocated space.

## 🥚 v1.0 - *Neumann*

*Focus:* The Foundation

- [x] **Core Execution Loop:** Basic REPL

- [x] **Basic Parsing:** Command tokenization via `strtok`

- [x] **Basic Process Management:** Implementation of `fork` and `execvp`

- [x] **Initial Built-ins:**
    - [x] *Basic `cd`*
    - [x] *`exit`*

## 🐣 v1.5 - *Neumann+*

*Focus:* POSIX Compliance

- [x] **Tilde Expansion:** Support for `cd ~` to cd into `$HOME` directory

- [x] **Home Shortcut:** Support for `cd` to cd into `$HOME` directory

- [x] **Previous Directory:** Support for `cd -` using `$OLDPWD` logic

- [x] **Environment Tracking:** Initial tracking of `PWD` and `OLDPWD`

## 🏺 v2.0 - *Babbage*

*Focus:* Separation of Functionality, Makefile

- [x] **Modular Structure:**
    - [x] `src/`
    - [x] `include/`
    - [x] `builtins/`

- [x] `makefile`

## 🐞 v2.5 - *Hopper*

*Focus:* Stability and Bug Squashing

- [x] **Error Handling:** Implement more descriptive error messages for failed
`chdir` calls.

- [x] **Environment Initialization:** Fix the bug where internal environment
variables are uninitialized on startup.

- [x] **Symlink Support:** Rewrite `cd` and `pwd` logic to distinguish between
logical paths and physical paths.

## 🔌 v3.0 - *Ritchie*

*Focus:* I/O, Redirection, Environment

- [x] **Redirection Engine:** Implement `<`, `>`, `>>`.

- [x] **The Pipe Operator:** Support for `|` to connect processes.

- [x] **Logical Path Tracking:** Ensure `cd` updates `PWD` with the user's input
string, and `pwd` reads from `PWD` before falling back to `getcwd()`.
    - **NOTE:** Add Check (If PWD doesn't exist or invalid, the shell should
    always fall back to `getcwd`. This makes the shell self-healing.)
