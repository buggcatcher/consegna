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

Project Goal

Create a simplified version of the Bash shell, called minishell, that can interpret user commands, execute programs, and handle basic shell features like redirections and pipes.
Core Technical Requirements (Mandatory Part)

Your shell must:

    Display a prompt (e.g., $> ) when waiting for a command.

    Maintain a working command history (using the readline library).

    Search for and launch executables using the PATH variable or via a relative/absolute path.

    Handle quoting:

        Single quotes ('): Prevent interpretation of all meta-characters inside.

        Double quotes ("): Prevent interpretation of most meta-characters, except for the $ (dollar sign) for variable expansion.

    Implement redirections:

        < Redirect input.

        > Redirect output (overwrite).

        << Here document (read input until a delimiter line).

        >> Redirect output (append).

    Implement pipes (|) to connect the output of one command to the input of the next.

    Expand environment variables:

        $VAR expands to its value.

        $? expands to the exit status of the last foreground command.

    Handle signals like Bash in interactive mode:

        ctrl-C (SIGINT): Displays a new prompt on a new line.

        ctrl-D (EOF): Exits the shell.

        ctrl-\ (SIGQUIT): Does nothing.

    Implement built-in commands:

        echo with the -n option

        cd

        pwd

        export

        unset

        env

        exit

Important Rules & Constraints

    Language: Must be written in C.

    Norminette: Code must comply with the school's Norm.

    Errors: No crashes (segfaults, bus errors, etc.) are allowed.

    Memory: No memory leaks are allowed (except for the known readline() leaks).

    Global Variables: Only one global variable is allowed, and it can only be used to store a received signal number (e.g., g_signal). It cannot be a structure.

    Makefile: Required with the rules $(NAME), all, clean, fclean, and re. It must compile with -Wall, -Wextra, and -Werror.

    Libraries: You are authorized to use your libft. The use of the readline and related termcap functions is mandatory and provided.

What is NOT Required (Mandatory Part)

    Interpreting backslashes (\) or semicolons (;).

    Handling unclosed quotes.

    Fixing memory leaks from the readline() library function.

Bonus Part

The bonus will only be evaluated if the mandatory part is 100% perfect.

    Logical operators: && (and) and || (or), with parentheses () for setting priority.

    Wildcards: The * wildcard should work for the current working directory.

Key Takeaway

This project is about deeply understanding process creation (fork, execve), file descriptor manipulation (dup2, pipe), and signal handling. The reference for any ambiguous behavior is the Bash shell.
