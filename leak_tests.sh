#!/bin/bash

# Run minishell under valgrind for each test case
run_test() {
    echo -e "\n===== TEST: $1 ====="
    echo -e "$2" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=supp.supp ./minishell
}

# 1. Empty inputs
run_test "empty line" ""
run_test "spaces" "     "
run_test "tabs" "\t\t\t"

# 2. Simple words
run_test "simple commands" "ls\necho\npwd\nexit"

# 3. Long word
run_test "long word" "$(printf 'a%.0s' {1..500})"

# 4. Quotes
run_test "double quotes" "echo \"hello world\""
run_test "single quotes" "echo 'hello world'"
run_test "mixed quotes" "echo \"hello'world\""

# 5. Unclosed quotes
run_test "unclosed double quote" "echo \"hello"
run_test "unclosed single quote" "echo 'hello"

# 6. Variable expansion
run_test "simple expansion" "echo \$USER"
run_test "mixed expansion" "echo \"\$USER \$HOME\""
run_test "no expansion in single quotes" "echo '\$USER'"

# 7. Redirections
run_test "redir out" "ls > out"
run_test "redir append" "ls >> out"
run_test "redir in" "cat < out"

# 8. Pipes
run_test "simple pipe" "ls | wc"
run_test "multiple pipes" "echo hello | cat | wc"

# 9. Syntax errors
run_test "pipe error" "|"
run_test "double pipe" "||"
run_test "invalid redir" "<<<"
run_test "redir then pipe" "> |"

# 10. Combined redirs + pipes
run_test "redir + pipe" "cat < out | grep a > out2"

# 11. Heredoc
run_test "heredoc" "cat << EOF\nhello\nEOF"

# 12. Builtins
run_test "cd tests" "cd /\ncd ..\ncd doesnotexist"
run_test "export tests" "export A=1\nexport B=2"
run_test "unset tests" "unset A"
run_test "exit tests" "exit 0\nexit 42"

# 13. Stress loop
run_test "stress 200 echos" "$(printf 'echo test\n%.0s' {1..200})"
