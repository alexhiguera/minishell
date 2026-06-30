# Minishell — 42 School 🐚🚀

> _As beautiful as a shell._ — Your own little `bash`, written from scratch in C.
> Processes, pipes and file descriptors, the hard way.

![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-C-blue)
![Norm](https://img.shields.io/badge/norminette-passing-success)
![Build](https://img.shields.io/badge/build-Wall%20Wextra%20Werror-orange)

```
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
```

## 📖 About

Minishell reimplements a useful subset of `bash`: it shows a prompt, reads a
command line, expands variables, splits it into a pipeline of commands with
redirections, and executes them — built-ins inside the shell, external programs
through `fork` + `execve` resolved against `PATH`.

The whole thing flows through five clean stages — **readline → lexer →
expander → parser → executor** — with a tiny `t_shell` context (environment +
last exit status) threaded through. Only **one global variable** exists, and
only to carry the number of a received signal, exactly as the subject demands.

Everything compiles with `-Wall -Wextra -Werror`, passes the **42 norminette**,
and frees every byte it allocates (`readline`'s own leaks aside).

> ⚠️ This is a learning project. If you're a 42 student, read the subject and
> build your own first — then compare. The goal is understanding the patterns,
> not copying.

## ✨ Features

| Area              | What works                                                              | Part      |
| ----------------- | ----------------------------------------------------------------------- | --------- |
| Prompt & history  | Interactive prompt, line editing, command history (`readline`)          | mandatory |
| Pipelines         | `cmd1 \| cmd2 \| cmd3` of any length                                     | mandatory |
| Redirections      | `<` input · `>` truncate · `>>` append · `<<` here-document             | mandatory |
| Quoting           | `'…'` fully literal · `"…"` literal except `$` expansion                 | mandatory |
| Expansion         | `$VAR` environment variables · `$?` last exit status                    | mandatory |
| Built-ins         | `echo -n` · `cd` · `pwd` · `export` · `unset` · `env` · `exit`          | mandatory |
| Signals           | `Ctrl-C` new prompt · `Ctrl-D` exit · `Ctrl-\` ignored (one global)     | mandatory |
| Exit codes        | Accurate `$?` (`0/1/2/126/127/130/128+sig`)                             | mandatory |
| Logical operators | `&&`, `\|\|` with short-circuit and `( )` for grouping/priority         | **bonus** |
| Wildcards         | `*` globbing against the current directory                              | **bonus** |

## 📊 Status — mandatory complete · bonus complete

| Build        | Command       | Files | Norminette | Result            |
| ------------ | ------------- | ----- | ---------- | ----------------- |
| Mandatory    | `make`        | 38    | ✅ 0 errors | ✅ fully working   |
| Bonus        | `make bonus`  | 42    | ✅ 0 errors | ✅ fully working   |

Both builds compile with `-Wall -Wextra -Werror`, do **not** relink, and the
`Makefile` builds `libft` first.

## 🗂️ Repository structure

```
.
├── Makefile              # all · bonus · clean · fclean · re (no relink)
├── libft/                # libft submodule (compiled first by the Makefile)
├── subject.pdf           # the official 42 subject
├── srcs/                 # mandatory part
│   ├── main.c            # entry point + REPL loop
│   ├── minishell.h       # structures, enums, prototypes
│   ├── env/              # environment as a linked list
│   ├── signals/          # signal setup + handler (single global)
│   ├── lexer/            # quote-aware tokenizer
│   ├── expand/           # $VAR / $? expansion and quote removal
│   ├── parser/           # tokens → command list + redirections
│   ├── exec/             # pipelines, PATH, redirections, heredoc
│   ├── builtins/         # echo, cd, pwd, export, unset, env, exit
│   └── utils/            # errors, cleanup
└── srcs_bonus/           # bonus part (*_bonus.c): adds && || ( ) + wildcards
    ├── parser/           # AST recursive-descent parser + glob matching
    └── exec/             # AST evaluator with short-circuit + subshells
```

## 🚀 How to use it

This project depends on the [`libft`](libft) submodule and the **readline**
library.

```bash
# 1. Clone with the submodule
git clone --recurse-submodules https://github.com/alexhiguera/minishell.git
cd minishell
# (if you forgot --recurse-submodules)
git submodule update --init --recursive

# 2. Build the mandatory part …
make
./minishell

# … or the bonus part (&& || ( ) and wildcards)
make fclean && make bonus
./minishell
```

> On macOS the `Makefile` auto-detects Homebrew `readline`
> (`brew install readline`); on Linux it links the system `-lreadline`.

```text
minishell$ echo "Hello, $USER" | tr a-z A-Z
HELLO, ALEX
minishell$ export GREETING=hi
minishell$ echo $GREETING $?
hi 0
minishell$ cat << EOF > out.txt
> a line for $USER
> EOF
minishell$ ls *.txt && echo found || echo missing
out.txt
found
minishell$ (cd /tmp && pwd) ; pwd
/private/tmp
/path/to/minishell
minishell$ exit
```

| Rule         | Effect                                              |
| ------------ | --------------------------------------------------- |
| `make`       | Build the mandatory `minishell`                     |
| `make bonus` | Build `minishell` with `&&`/`\|\|`/`()`/wildcards   |
| `make clean` | Remove object files                                 |
| `make fclean`| Remove objects and the binary                       |
| `make re`    | `fclean` + `make`                                   |

## 🎯 Notes & scope

- The grader compiles with `-Wall -Wextra -Werror`: a single warning is zero
  points — both builds are warning-clean.
- Bonus is only graded if the mandatory part is **perfect**, so the mandatory
  part is the priority and is feature-complete.
- A couple of deliberate simplifications (outside the subject's requirements):
  no field-splitting of expanded variables, and `cmd | (subshell)` is not
  supported (parentheses act as a command/priority group).
- `readline` itself may leak; the shell's own allocations are all freed.

## 🤝 Contributing

Found a bug, a cleaner approach, or a missing edge case? Issues and PRs are
welcome — just make sure your change compiles cleanly with
`-Wall -Wextra -Werror`, passes the norminette, and doesn't leak.

## 📜 License

Released under the [MIT License](LICENSE) — free to use, learn from, and share.

If this repo helped you, consider leaving a ⭐ — it helps other students find it.

Made with ☕ and a lot of `-Wall -Wextra -Werror` by **Alex Higuera**
