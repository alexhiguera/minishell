
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

# Minishell

> _As beautiful as a shell._ — A small, POSIX-flavoured Unix shell written in C
> for the 42 curriculum.

Minishell reimplements a useful subset of `bash`: it reads a command line,
expands variables, splits it into a pipeline of commands with redirections,
and executes them — built-ins in the shell process, external programs through
`fork` + `execve` resolved against `PATH`.

## Features 🐚

- **Interactive prompt** with line editing and a working command **history**
  (via `readline`).
- **Pipelines** of arbitrary length: `cmd1 | cmd2 | cmd3`.
- **Redirections**:
  - `<`  — redirect input
  - `>`  — redirect output (truncate)
  - `>>` — redirect output (append)
  - `<<` — here-document (reads until the delimiter; expands `$` unless the
    delimiter is quoted)
- **Quoting**: single quotes `'…'` keep everything literal; double quotes
  `"…"` keep everything literal **except** `$` expansion.
- **Expansion**: environment variables `$VAR` and the last exit status `$?`.
- **Built-ins**: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`,
  `exit`.
- **Signals** (interactive), mirroring bash:
  - `Ctrl-C` prints a fresh prompt on a new line
  - `Ctrl-D` exits the shell
  - `Ctrl-\` does nothing
- **Accurate exit codes** (`0`, `1`, `2`, `126`, `127`, `128 + signal`,
  `130`, …) exposed through `$?`.

Only a single global variable is used, and solely to carry the number of a
received signal — as required by the subject.

## Build 🛠️

The project depends on the [`libft`](libft) submodule and the **readline**
library.

```bash
# 1. Clone with the submodule
git clone --recurse-submodules https://github.com/alexhiguera/minishell.git
cd minishell

# (or, if you already cloned without --recurse-submodules)
git submodule update --init --recursive

# 2. Build
make
```

The `Makefile` compiles `libft` first, then the shell, with
`-Wall -Wextra -Werror` and no relink. On macOS it automatically picks up the
Homebrew `readline` (`brew install readline`); on Linux it links the system
`-lreadline`.

| Rule      | Effect                                         |
| --------- | ---------------------------------------------- |
| `make`    | Build `minishell` (default `all`)              |
| `clean`   | Remove object files                            |
| `fclean`  | Remove object files and the binary             |
| `re`      | `fclean` + `all`                               |

## Usage 🎮

```bash
./minishell
```

```text
minishell$ echo "Hello, $USER" | tr a-z A-Z
HELLO, ALEX
minishell$ export GREETING=hi
minishell$ echo $GREETING $?
hi 0
minishell$ cat << EOF > out.txt
> line for $USER
> EOF
minishell$ ls -la | grep out.txt
-rw-r--r--  1 alex  staff  16 ...
minishell$ exit
```

## Project layout 🗂️

```
srcs/
├── main.c            # entry point + REPL loop
├── minishell.h       # structures, enums, prototypes
├── env/              # environment as a linked list (get/set/unset/to-array)
├── signals/          # signal setup + handler (single global)
├── lexer/            # tokenizer (quote-aware) → token list
├── expand/           # $VAR / $? expansion and quote removal
├── parser/           # tokens → command list with redirections + syntax checks
├── exec/             # pipeline execution, PATH resolution, redirs, heredoc
├── builtins/         # echo, cd, pwd, export, unset, env, exit
└── utils/            # errors, cleanup helpers
```

The data flows in stages: `readline` → **lexer** → **expander** → **parser** →
**executor**, with a small `t_shell` context (environment, last exit status)
threaded through.

## Notes 📝

- This repository implements the **mandatory** part of the subject. The bonus
  (`&&`, `||`, parentheses, wildcards) is intentionally not implemented.
- `readline` itself may leak memory; the shell's own allocations are freed.

## License 📄

Released under the [MIT License](LICENSE).
