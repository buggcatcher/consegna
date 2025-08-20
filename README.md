# minishell

```shell
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
