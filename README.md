# minishell

![MiniShell Demo](https://raw.githubusercontent.com/buggcatcher/public/main/various/minishow.gif)

This Bash-like shell allows you to:

- Display a prompt whenever it is waiting for user input.
- Use command history with arrow keys and autocomplete with the Tab key.
- Correctly handle single and double quotes.
- Handle redirections (input/output).
- Handle pipes so that the output of one command is passed as input to the next.
- Support environment variable expansion, including cases like `$?`, `$$`, and `$0`.
- Handle signals in interactive mode.
- Locate and execute the correct binary, based on the `PATH` variable or relative/absolute paths.
- Support custom built-in commands.

---

Here are just a few of the commands tested without memory leaks, still‑reachable allocations, dangling pointers, or unclosed file descriptors when performing redirections.

```bash
🔹minishell❯ mkdir test
🔹minishell❯ export test_path=/home/kali/Desktop/test
🔹minishell❯ export | grep test_path
🔹minishell❯ cd $test_path
🔹minishell❯ > test.file
🔹minishell❯ < input.txt | cat 
🔹minishell❯ cat < input.txt > output.txt
🔹minishell❯ < input.txt cat > output.txt
🔹minishell❯ cat > output.txt < input.txt
🔹minishell❯ > output.txt < input.txt cat
🔹minishell❯ echo "user $USER is at $PWD with $0" > user.info
🔹minishell❯ echo "last exit status is $?. last pid is $$" | cat -e >> user.info
🔹minishell❯ cat test.file
🔹minishell❯ echo "hello world" -n
🔹minishell❯ echo $HOME$
🔹minishell❯ echo $$$USER
🔹minishell❯ echo “ls | incorrect”
🔹minishell❯ echo |
🔹minishell❯ echo ciao | echo ciao | echo ciao 
🔹minishell❯ echo hello >> file.txt 
🔹minishell❯ echo ciao | file.txt 
🔹minishell❯ echo ciao | cat -e
🔹minishell❯ ls -lha
🔹minishell❯ touch doc1.txt doc2.txt doc3.txt
🔹minishell❯ ls | grep "file.txt  "
🔹minishell❯ cat “file.txt “
🔹minishell❯ ls -1 | grep ".txt" | sort > lista_documenti_ordinati.txt
🔹minishell❯ ls | ls | ls
🔹minishell❯ touch $PATH/file
🔹minishell❯ export _key1=""
🔹minishell❯ export _key2=
🔹minishell❯ export _key3=value
🔹minishell❯ export _key4="value"
🔹minishell❯ export _key5
🔹minishell❯ env | grep key
🔹minishell❯ export | grep key
🔹minishell❯ unset _key1 _key2 _key3 _key4 _key5
🔹minishell❯ cat | cat | cat
🔹minishell❯ wc < nofile
🔹minishell❯ foo
🔹minishell❯ ls | foo 
🔹minishell❯ ls | foo << x 
🔹minishell❯ foo cat < x.file 
🔹minishell❯ foo | foo | foo 
🔹minishell❯ echo "last exit status is $?. last pid is $$”
🔹minishell❯ htop
🔹minishell❯ nautilus .
🔹minishell❯ cat << x | cat << x
🔹minishell❯ echo << x >> file.file
🔹minishell❯ cat << x > file.file
🔹minishell❯ cat << x >> “file.txt “
🔹minishell❯ echo << x | foo 
🔹minishell❯ cat << EOF
  > user $USER
  > is using $0
  > at $PWD
  > EOF
🔹minishell❯ << x << y << z                                                                                                                                                                                                                     
  > x
  > gg
  > y
  > wp
  > z
🔹minishell❯ exit
🔹minishell❯ exit 255
```

## Project Goal

Create a simplified version of the Bash shell, called `minishell`, that can interpret user commands, execute programs, and handle basic shell features like redirections and pipes.

## Requirements

Your shell must implement the following features:

### Basic Functionality
- Display a prompt (e.g., `$> `) when waiting for a command
- Maintain a working command history using the `readline` library
- Search for and launch executables using the `PATH` variable or via relative/absolute paths

### Quoting Handling
- **Single quotes (`'`)**: Prevent interpretation of all meta-characters inside
- **Double quotes (`"`)**: Prevent interpretation of most meta-characters, except for `$` (dollar sign) for variable expansion

### Redirections
- `<` Redirect input
- `>` Redirect output (overwrite)
- `<<` Here document (read input until a delimiter line)
- `>>` Redirect output (append)

### Pipes
- Implement pipes (`|`) to connect the output of one command to the input of the next

### Variable Expansion
- `$VAR` expands to its environment value
- `$?` expands to the exit status of the last foreground command

### Signal Handling
- `ctrl-C` (SIGINT): Displays a new prompt on a new line
- `ctrl-D` (EOF): Exits the shell
- `ctrl-\` (SIGQUIT): Does nothing

### Built-in Commands
- `echo` with the `-n` option
- `cd` with relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

## ⚙️ Technical Constraints

### Code Requirements
- Written in **C**
- Must comply with the Norminette code style
- No crashes allowed (segfaults, bus errors, etc.)
- No memory leaks (except known `readline()` library leaks)
- Only **one global variable** allowed, exclusively for storing signal numbers

### Makefile Requirements
- Must contain rules: `$(NAME)`, `all`, `clean` and `re`
- Must compile with flags: `-Wall`, `-Wextra`, and `-Werror`
- Must handle own library dependencies

### External Functions
The project allows use of various system calls and library functions including:
- `readline`, `add_history` for input handling
- `fork`, `execve`, `waitpid` for process management
- `open`, `close`, `dup`, `dup2` for file descriptor manipulation
- `pipe` for inter-process communication
- `signal`, `sigaction` for signal handling

## ❌ Not Required (Mandatory Part)
- Interpreting backslashes (`\`) or semicolons (`;`)
- Handling unclosed quotes
- Fixing memory leaks from the `readline()` library function

## 🏆 Bonus Part

### Bonus Features
- **Logical operators**: `&&` (and) and `||` (or)
- **Parentheses** `()` for setting operation priority
- **Wildcards**: The `*` wildcard should work for the current working directory

## 🧠 Key Learning Outcomes

This project focuses on understanding:
- Process creation (`fork`, `execve`)
- File descriptor manipulation (`dup2`, `pipe`)
- Signal handling in an interactive program
- Environment variable management
- Parsing and interpreting user input

## 📝 Reference Implementation

For any ambiguous behavior, **Bash** should be used as the reference implementation.
