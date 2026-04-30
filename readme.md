*This project has been created as part of the 42 curriculum by side-lan, jjhurry.*

#  Minishell

A Unix shell implementation in C, built as part of the 42 school curriculum.

---

## Description

Minishell is a lightweight bash-like shell written in C. The goal of the project is to deeply understand how a Unix shell works by reimplementing its core behavior from scratch -- including command parsing, execution, piping, redirections, environment variable management, signal handling, and built-in commands.

The shell supports interactive use via `readline` as well as non-interactive execution via piped input, closely mirroring the behavior of bash.

### Features

- **Interactive prompt** using GNU readline with command history (arrow keys, `Ctrl+R`, etc.)
- **Command execution** via `execve`, searching `PATH` for executables
- **Pipes** -- chaining commands with `|`
- **Redirections** -- `<`, `>`, `>>`, and `<<` (heredoc)
- **Environment variable expansion** -- `$VAR`, `$?`, handling of quoted and unquoted contexts
- **Quote handling** -- single quotes (no expansion), double quotes (expansion preserved)
- **Signal handling** -- `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave as in bash
- **Built-in commands** implemented natively:
  - `echo` with `-n` flag
  - `cd` with relative and absolute paths
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## Instructions

### Installation

```bash
# Clone the repository
git clone git@vogsphere-v2.codam.nl:vogsphere/intra-uuid-51bc2015-18e4-4574-b2f6-8add30f3fee1-7185983-side-lan minishell
cd minishell

# Install readline if needed (Ubuntu/Debian)
sudo apt install libreadline-dev

# Build
make
```

### Running

**Interactive mode:**
```bash
./minishell
```

**Non-interactive mode (piped input):**
```bash
echo "echo hello world" | ./minishell
```

### Cleaning up

```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full rebuild
```

---

## Usage Examples

```bash
# Basic commands
Minishell> echo "hello world"
hello world

# Environment variables
Minishell> export NAME=42
Minishell> echo $NAME
42

# Pipes
Minishell> cat file.txt | grep hello | wc -l

# Redirections
Minishell> echo hi > outfile
Minishell> cat < infile >> outfile

# Heredoc
Minishell> cat << EOF
> line one
> line two
> EOF

# Exit codes
Minishell> ls nonexistent
ls: cannot access 'nonexistent': No such file or directory
Minishell> echo $?
2
```

---

## Project Structure

```
minishell/
├── exec/               # Execution engine (forking, pipes, builtins, redirections)
│   ├── includes/
│   └── src/
├── parser/             # Lexer, tokenizer, expansion, quote handling
│   ├── includes/
│   └── src/
|
├── Makefile
└── README.md
```

---

## Resources

### Documentation & References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) -- the primary reference for expected shell behavior
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) -- documentation for the readline API used for the interactive prompt
- [The Linux Programming Interface](https://man7.org/tlpi/) -- Michael Kerrisk's comprehensive guide to Linux system calls (fork, execve, pipe, signals, etc.)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/) -- W. Richard Stevens, foundational reference for Unix process and I/O model
- [`man` pages](https://man7.org/linux/man-pages/) -- `execve(2)`, `fork(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `signal(7)`, `sigaction(2)`


### Articles & Tutorials

- [Writing a Unix Shell](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/) -- three-part blog series covering shell fundamentals
- [Coding your own Shell in C](https://medium.com/@santiagobedoa/coding-a-shell-using-c-1ea939f10e7e) -- A blog about how to create a shell, aswell as the inner workings of a shell
- [Shell Command Language (POSIX)](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) -- POSIX specification for shell behavior
- [What Are Builints](https://unix.stackexchange.com/questions/11454/what-is-the-difference-between-a-builtin-command-and-one-that-is-not) -- A discussion about shell buil in functions

### AI Usage

Claude (Anthropic) was used throughout this project as a development assistant. Specific uses included:

- **Debugging** -- identifying bugs in C code through code review (off-by-one errors, missing `== 0` on `strncmp`, uninitialized pointers, wrong `write` lengths, etc.)
- **Architecture guidance** -- discussing design decisions such as environment variable ownership, heredoc processing order (parent vs child), signal handling strategy, and the `data->envp` single source of truth pattern
- **Valgrind output interpretation** -- parsing and explaining memory error traces to identify root causes
- **Parsing logic** -- brainstormed ideas how to handle parsing and designing the used data structure
- **Built-in command behavior** -- clarifying exact bash behavior for edge cases in `export`, `unset`, `echo`, `cd`, `exit`, and `$?` expansion
- **README document structute** -- used to make a layout for this document and suggest content

All code was written by the project authors. AI was used for guidance, review, and debugging -- not for generating production code.

---
