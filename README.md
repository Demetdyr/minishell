# minishell

**minishell** is a minimal Unix shell implemented in C, designed as a learning project to understand how shells work internally. It supports command parsing, execution, redirections, pipes, environment variable management, and built-in commands, closely mimicking the behavior of standard shells like `bash` or `zsh`.

## Features

- **Command Execution**: Run external programs with arguments.
- **Built-in Commands**: Includes `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Pipes**: Chain commands using the `|` operator.
- **Redirections**: Supports input `<`, output `>`, append `>>`, and heredoc `<<`.
- **Environment Variables**: Handles variable expansion and management.
- **Quotes Handling**: Correctly parses single and double quotes.
- **Error Handling**: Provides user-friendly error messages for syntax and execution errors.
- **Signal Handling**: Handles `Ctrl+C`, `Ctrl+D`, and heredoc interruptions gracefully.
- **History**: Command history support via GNU Readline.

## Build Instructions

1. **Dependencies**:  
   - GCC or Clang
   - GNU Readline library
   - Make

2. **Clone the repository**:
   ```sh
   git clone https://github.com/Demetdyr/minishell.git
   cd minishell
   ```

3. **Build the project:**
   ```sh
   make
   ```

   The executable will be created in the `bin/` directory.

## Usage

Run the shell:
```sh
./bin/minishell
```

You can now enter commands as you would in a typical shell. For example:
```sh
echo "Hello, World!"
ls -l | grep Makefile > output.txt
cat < input.txt | sort
export MYVAR=42
echo $MYVAR
```

## Project Structure

- [`cmd`](cmd ) — Entry point ([`cmd/minishell.c`](cmd/minishell.c ))
- [`src`](src ) — Source files for parsing, execution, built-ins, redirections, etc.
- [`inc`](inc ) — Header files
- [`Makefile`](Makefile ) — Build instructions

## Not Implemented

- Wildcard expansion (globbing)
- Job control (background/foreground processes)
- Advanced shell scripting features

## Authors

- [Demet Duyar](https://github.com/Demetdyr)
- [Mehmet Efe Çakır](https://github.com/Efe-MEC)

## License

This project is for educational purposes and does not have a specific license.