# Minishell

A simple Unix shell written in C as part of the 42 curriculum.

The goal of the project was to understand how a shell works by implementing command parsing, environment variables, pipes, redirections, built-in commands, processes and signals.

## Features

* Command parsing and execution
* Pipes
* Input and output redirections
* Environment variables
* Signal handling
* Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
* External command execution using `$PATH`

## Project Structure

```text
inc/        Header files

lib/        External libraries (libft)

src/
├── cmd/    Built-in and external command handling
├── env/    Environment variable management
├── exec/   Execution, processes, pipes and redirections
├── help/   Utility functions
├── main/   Entry point and shell loop
└── pars/   Lexing and parsing
```

## Build

```bash
make
```

Run with:

```bash
./minishell
```

## Authors

Jérémie Debrulle
Anais Gouby
