# Current Status : `v2.0` Modularization Complete

* The monolithic `jayshell.c` has been successfully split into `src/`,
`builtins/`, and `include/`.
* Modular build system via `makefile` is implemented.
* `cd -` and `cd ~` fully functional.

---

# Roadmap for Jayshell

## v3.0 - *Ritchie*

*Focus:* I/O, Redirection, Environment

- [ ] **Environment Initialization Bug:** Fix the bug where variables aren't
initialized on startup.

- [ ] **Redirection Engine:** Implement <, >, >>, and 2> (stderr).

- [ ] **The Pipe Operator:** Support for | to connect processes.

- [ ] **Logical Execution:** Implement && (AND) and || (OR).

- [ ] **Built-ins:**
    - [ ] `echo`: With -n and -e flag support.
    - [ ] `export`: To set environment variables.
    - [ ] `unset`: To remove variables.
    - [ ] `env`: To list current environment.
    - [ ] `pwd`: (Already modularized, ensure it handles symlinks).

## v4.0 - *Thompson*

*Focus:* Stability, Signal Handling, Job Control

- [ ] **Signal Handling:** Correctly handle SIGINT (Ctrl+C), SIGQUIT (Ctrl+),
and SIGTSTP (Ctrl+Z).

- [ ] **Job Control:** Support for backgrounding with &.

- [ ] **Built-ins:**
    - [ ] `jobs`: List active background tasks.
    - [ ] `fg` / `bg`: Move jobs between foreground and background.
    - [ ] `kill`: Send signals to processes by PID or Job ID.
    - [ ] `history`: Integrated with ~/.jayshell_history for persistence.

## v5.0 - *Lovelace*

*Focus:* Customization, Script Execution, Alias Logic

- [ ] **Shebang Support:** Allow execution of scripts starting with #!.

- [ ] **Startup Files:** Load .jayshellrc and .jayshell_aliases on init.

- [ ] **Git Integration:** Dynamic prompt with status indicators.

- [ ] **Built-ins:**
    - [ ] `source` / `.` : Execute scripts in the current shell context.
    - [ ] `alias` / `unalias`: Create and remove command shortcuts.
    - [ ] `type`: Identify if a command is a built-in, alias, or file.
    - [ ] `read`: Take user input into a variable.
    - [ ] `wait`: Wait for background processes to complete.

## v6.0 - *Chomsky*

*Focus:* Transitioning to a Formal Grammar with Flex & Bison.

- [ ] **The Lexer/Parser Rewrite:** Move away from `strtok` to a formal grammar.

- [ ] **Expansion Engine:**
    - [ ] *Quote Handling:* Single `'` and double `"` quotes.
    - [ ] *Escape Characters:* Support for `\`.
    - [ ] *Command Substitution:* `$(command)`.
    - [ ] *Globbing:* Wildcard expansion `*` and `?`.

- [ ] **Built-ins:**
    - [ ] `printf`: More robust output formatting.
    - [ ] `hash`: Command location caching for performance.

## v7.0 - *Turing*

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

# DONE

- [x] **v2.0:** Modular architecture, `makefile`
- [x] **v1.0:** Basic loop, fork/exec, `exit`, `cd`, `cd -`, `cd ~`
