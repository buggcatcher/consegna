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
🔹minishell❯ echo << x >> file.file
🔹minishell❯ cat << x > file.file
🔹minishell❯ cat << x >> “file.txt “
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
🔹minishell❯ cat << x | cat << x 
🔹minishell❯ cat | cat | cat
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
🔹minishell❯ wc < nofile
🔹minishell❯ foo
🔹minishell❯ echo << x | foo 
🔹minishell❯ ls | foo 
🔹minishell❯ ls | foo << x 
🔹minishell❯ foo cat < x.file 
🔹minishell❯ foo | foo | foo 
🔹minishell❯ echo "last exit status is $?. last pid is $$”
🔹minishell❯ htop
🔹minishell❯ nautilus .
🔹minishell❯ exit
🔹minishell❯ exit 255
```
