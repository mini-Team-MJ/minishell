#!/bin/bash

# Minishell 포괄적 테스트 스크립트
# 사용법: ./test_minishell.sh

RESULT_FILE="result.txt"
MINISHELL="./minishell"
TEST_DIR="test_files"

# 색상 정의
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 결과 파일 초기화
echo "=== MINISHELL TEST RESULTS ===" > $RESULT_FILE
echo "Test Date: $(date)" >> $RESULT_FILE
echo "===============================" >> $RESULT_FILE
echo "" >> $RESULT_FILE

# 테스트 디렉토리 생성
mkdir -p $TEST_DIR
cd $TEST_DIR

# 테스트용 파일들 생성
echo "Hello World" > test_input.txt
echo "Line 1" > test_append.txt
echo "test content for grep" > grep_test.txt
echo -e "apple\nbanana\ncherry" > fruit.txt
mkdir -p test_subdir

# 테스트 함수
run_test() {
    local test_name="$1"
    local commands="$2"
    
    echo -e "${BLUE}Testing: $test_name${NC}"
    echo "=== $test_name ===" >> ../$RESULT_FILE
    echo "Commands: $commands" >> ../$RESULT_FILE
    echo "Output:" >> ../$RESULT_FILE
    
    # minishell에 명령어들 전달하고 결과 저장
    echo -e "$commands\nexit" | timeout 10s ../$MINISHELL >> ../$RESULT_FILE 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo "TIMEOUT - Test took longer than 10 seconds" >> ../$RESULT_FILE
    elif [ $exit_code -ne 0 ]; then
        echo "EXIT CODE: $exit_code" >> ../$RESULT_FILE
    fi
    
    echo "---" >> ../$RESULT_FILE
    echo "" >> ../$RESULT_FILE
}

echo -e "${GREEN}Starting Minishell Tests...${NC}"

# 1. 빌트인 명령어 테스트
echo -e "${YELLOW}1. Testing Builtins...${NC}"

run_test "PWD builtin" "pwd"

run_test "ECHO builtin - simple" "echo Hello World"

run_test "ECHO builtin - with -n" "echo -n No newline"

run_test "CD builtin - relative path" "cd test_subdir\npwd\ncd ..\npwd"

run_test "CD builtin - home directory" "cd\npwd"

run_test "ENV builtin" "env"

run_test "EXPORT builtin - set variable" "export TEST_VAR=hello\necho \$TEST_VAR"

run_test "EXPORT builtin - show all" "export"

run_test "UNSET builtin" "export TEST_VAR2=world\necho \$TEST_VAR2\nunset TEST_VAR2\necho \$TEST_VAR2"

run_test "EXIT builtin - with code" "exit 42"

# 2. 외부 명령어 테스트
echo -e "${YELLOW}2. Testing External Commands...${NC}"

run_test "LS command" "ls"

run_test "LS with options" "ls -la"

run_test "CAT command" "cat test_input.txt"

run_test "GREP command" "grep test grep_test.txt"

run_test "WC command" "wc fruit.txt"

run_test "Nonexistent command" "nonexistent_command"

run_test "Command with absolute path" "/bin/echo Absolute path test"

run_test "Command with relative path" "./minishell --version"

# 3. 리디렉션 테스트
echo -e "${YELLOW}3. Testing Redirections...${NC}"

run_test "Output redirection >" "echo Redirect test > redirect_out.txt\ncat redirect_out.txt"

run_test "Append redirection >>" "echo First line > append_test.txt\necho Second line >> append_test.txt\ncat append_test.txt"

run_test "Input redirection <" "cat < test_input.txt"

run_test "Input and output redirection" "cat < test_input.txt > combined_test.txt\ncat combined_test.txt"

run_test "Multiple redirections" "echo Test > file1.txt\necho More >> file1.txt\ncat < file1.txt > file2.txt\ncat file2.txt"

# 4. 파이프 테스트
echo -e "${YELLOW}4. Testing Pipes...${NC}"

run_test "Simple pipe" "ls | grep test"

run_test "Multiple pipes" "cat fruit.txt | grep a | wc -l"

run_test "Pipe with builtin" "echo Hello World | cat"

run_test "Long pipe chain" "ls | head -5 | tail -3 | cat"

run_test "Pipe with redirection" "ls | grep minishell > pipe_output.txt\ncat pipe_output.txt"

# 5. 히어독 테스트
echo -e "${YELLOW}5. Testing Here Documents...${NC}"

run_test "Basic heredoc" "cat << EOF\nHello from heredoc\nSecond line\nEOF"

run_test "Heredoc with variables" "cat << END\nCurrent directory: \$PWD\nEND"

run_test "Heredoc to file" "cat << HEREDOC > heredoc_output.txt\nThis is heredoc content\nLine 2\nHEREDOC\ncat heredoc_output.txt"

# 6. 환경변수 및 특수 변수 테스트
echo -e "${YELLOW}6. Testing Environment Variables...${NC}"

run_test "Environment variable expansion" "echo \$HOME"

run_test "Exit status variable" "ls nonexistent\necho Exit status: \$?"

run_test "Exit status after success" "echo success\necho Exit status: \$?"

run_test "Custom environment variable" "export MY_VAR=custom_value\necho \$MY_VAR"

# 7. 쿼트 테스트
echo -e "${YELLOW}7. Testing Quotes...${NC}"

run_test "Single quotes" "echo 'Single quote test with \$HOME'"

run_test "Double quotes" "echo \"Double quote test with \$HOME\""

run_test "Mixed quotes" "echo 'Single' \"Double\" Mixed"

# 8. 복합 테스트
echo -e "${YELLOW}8. Testing Complex Scenarios...${NC}"

run_test "Complex pipe and redirection" "ls | grep test | cat > complex_output.txt\ncat complex_output.txt"

run_test "Multiple commands with semicolon equivalent" "echo First\necho Second\necho Third"

run_test "Environment in pipe" "export PIPE_VAR=pipe_test\necho \$PIPE_VAR | cat"

run_test "Builtin in pipeline" "echo test | grep test | wc -l"

# 9. 에러 케이스 테스트
echo -e "${YELLOW}9. Testing Error Cases...${NC}"

run_test "Permission denied" "cat /etc/shadow"

run_test "Directory as command" "test_subdir"

run_test "Invalid redirection" "echo test > /dev/null/invalid"

run_test "Broken pipe" "ls | exit"

# 10. 시그널 테스트 (간접적)
echo -e "${YELLOW}10. Testing Signal Handling...${NC}"

run_test "Ctrl-C simulation in script" "sleep 1"

# 테스트 정리
cd ..
rm -rf $TEST_DIR

echo -e "${GREEN}All tests completed!${NC}"
echo -e "${BLUE}Results saved in: $RESULT_FILE${NC}"
echo ""
echo -e "${YELLOW}Summary:${NC}"
echo "- Total test categories: 10"
echo "- Check $RESULT_FILE for detailed results"
echo "- Look for TIMEOUT, segfaults, or unexpected outputs"
