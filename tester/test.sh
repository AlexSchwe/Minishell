# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	#TEST1=$(echo $@ "; exit" | ./minishell 2>&-) #original
	TEST1=$(echo $@ "; exit" 2>&-| ./minishell  )
	ES_1=$?
	#TEST1=$(A=$TEST1; echo "$TEST1" | head -n1 | cut -d " " -f2-; echo "$A" | tail -n+2)
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | |  . \`| | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

### NOS TESTS ###
echo "En blanc:la sortie d'erreur de notre shell"
# ECHO TESTS
printf $YELLOW'ECHO TESTS (l68)\n'$RESET

exec_test 'echo -n -nnn hello -n ; echo a ; echo $?'
exec_test '$"hello"'
exec_test 'echo -n -n -nnnn -nnnnm ; echo a ; echo $?'

# CD TESTS
printf $YELLOW'CD TESTS (l%d)\n'$RESET "$LINENO"

exec_test 'unset HOME; cd ; echo $?; pwd ; echo $PWD'
exec_test 'mkdir a; mkdir a/b; cd a/b; rm -r ../../a; cd .. ; echo $?; pwd; echo $PWD'
exec_test 'export HOME= ; cd ; echo $? ; pwd ; echo $PWD'
exec_test 'export CDPATH="/" ; cd home/user42 ; echo $?; pwd; echo $PWD'
exec_test 'export CDPATH="/" ; cd home/.. ; echo $?; pwd; echo $PWD'
exec_test 'cd too many arguments ; echo $?'
exec_test 'cd $HOME/Bureau ; echo $?; pwd ; echo $PWD'
exec_test 'cd /home/user42/; echo $?; pwd ; echo $PWD'
exec_test 'cd ./path_not_found ; echo $?'
exec_test 'cd ../../../../../.. ; echo $?; pwd; echo $PWD'
exec_test 'cd .. ; echo $?; pwd; echo $PWD'
exec_test 'cd . ; echo $?; pwd; echo $PWD'
exec_test 'cd - ; echo $?'

# EXIT STATUS TESTS
printf $YELLOW'EXIT STATUS TESTS (l%d)\n'$RESET "$LINENO"

exec_test 'not_cmd ; echo $?'
exec_test 'exit dfsfs'
exec_test 'ls bonjour ; echo $?'
exec_test 'file_name'
exec_test 'export test=a ; echo $test ; echo $?'
exec_test 'cd random_cmd ; echo $?'
exec_test 'cd random_cmd ; cd $? ; echo $?'
exec_test 'cat bla'
exec_test './file_that_is_not_an_executable ;echo $?'
exec_test ''

# EXPORT TEST
printf $YELLOW'EXPORT TEST (l%d)\n'$RESET "$LINENO"

exec_test 'Export PATH=""'
exec_test 'export var=a ; export $var=test ; echo $var $a ; echo $?'
exec_test 'export var ; export var=test ; echo $?'
exec_test 'export la même variable ; echo $?'
exec_test 'unset var ; export $var=test ; echo $?'
exec_test 'unset var ; export $var ; echo $?'
exec_test 'unset test ; export "" test=a'

# INIT TEST
printf $YELLOW'INIT TEST (l%d)\n'$RESET "$LINENO"

exec_test 'env -i ./minishell puis echo $SHLVL'
exec_test 'env -i ./minishell'
exec_test '$SHLVL'

# PARSING TEST
printf $YELLOW'PARSING TEST (l%d)\n'$RESET "$LINENO"

exec_test 'echo bonjour \; ls ; echo $?'
exec_test 'echo $USER$var\$USER$USER\$USERtest$USER'
exec_test 'echo $SHLVL'
exec_test 'echo \>'
exec_test 'echo "bip | bip ; coyotte > < \" "'
exec_test 'echo "12\""'
exec_test 'echo "\s" ; echo "\\s"'
exec_test '$LESS$VAR'
exec_test '$'
exec_test '""'
exec_test '|'
exec_test '..'
exec_test 'export "test=ici"=coucou ; echo $test'
exec_test 'export ""; unset ""'
exec_test 'echo\ a ; echo $?'
exec_test 'echo \a ; echo $?'
exec_test 'echo "" bonjour ; echo $?'

# PIPE TEST
printf $YELLOW'PIPE TEST (l%d)\n'$RESET "$LINENO"

exec_test 'sleep 5 | exit'
exec_test 'ls bonjour | hello'
exec_test 'ls | exit'
exec_test 'cat Makefile | grep pr | head -n 5 | hello'
exec_test 'cat Makefile | grep pr | head -n 5 | cd file_not_exit'
exec_test 'cat | cat | cat | ls'

# REDIR TEST
printf $YELLOW'REDIR TEST (l%d)\n'$RESET "$LINENO"

exec_test 'not_cmd bonjour > salut'
exec_test 'echo test > file test1'
exec_test 'echo bonjour > test\ 1'
exec_test 'echo 2 >> out1 > out2'
exec_test 'echo 2 > out1 >> out2'
exec_test 'cat < test'
exec_test 'cat -e > test1 < test2'
exec_test '>file'
exec_test '>a ls >b >>c >d'
exec_test '>a ls <machin >>c >d avec machin n'exite pas'
exec_test '>a cat <b >>c'
exec_test '> test | echo blabla; rm test'
exec_test '<a cat <b <c avec b n'existe pas (ou pas les droits)'
exec_test '<a cat <b <c'

# SIGNAUX TEST
printf $YELLOW'SIGNAUX (l%d)\n'$RESET "$LINENO"

exec_test 'ctrl-C'
exec_test 'ctrl-\'

# SUBS TEST
printf $YELLOW'SUBS TEST (l%d)\n'$RESET "$LINENO"

exec_test 'unset $bla ; $bla echo lol ; echo $?'
exec_test 'export var=s\ -la ; l$var'
exec_test 'export var=at ; c$var Makefile'
exec_test 'export var="truc "; echo $var?'
exec_test 'export var=" truc"; echo $var'
exec_test 'export test=123\\ ; echo $test'
exec_test 'export test=123\" ; echo $test'
#exec_test 'export test=123\' ; echo $test ; echo $test'
exec_test 'export test="foo bar " ; echo ab$test'
exec_test 'export test=" foo bar " ; echo ab"$test" | cat -e'
exec_test 'export test=" foo bar " ; echo "$test"'
exec_test 'export test=" foo bar " ; echo ""$test""'
exec_test 'export test=" foo bar " ; echo """$test"""'
exec_test 'export test=" foo bar " ; echo ab$test'
exec_test 'export test=" foo bar " ; echo $test$test$'
exec_test 'export test=" foo bar " ; echo $test$'
exec_test 'export test=" foo bar " ; echo $test'
exec_test 'export test=" foo bar " ; echo "ab"$test'
exec_test 'export loop='bonjour$loop' ; echo $loop'

exec_test 'echo $"hola"'
exec_test 'echo "$tests"Makefile'
exec_test 'echo "$tests""Makefile"'
exec_test 'echo "$tests" "Makefile"'
exec_test 'echo "'abc'"'
exec_test 'echo '"abc"''

# SUBS & REDIR TEST
printf $YELLOW'SUBS & REDIR TEST (l%d)\n'$RESET "$LINENO"

exec_test 'unset test ; echo 3 >$test'
exec_test 'export test="file1 file2" ; echo 3 >"$test"'
exec_test 'export test="file1 file2" ; >$test'

# SYNTAXT TEST
printf $YELLOW'SYNTAXT TEST (l%d)\n'$RESET "$LINENO"

exec_test 'unset test ; echo bonjour > $test w/ test="o1 o2"'
exec_test 'unset test ; echo bonjour > $test'
exec_test 'echo bonjour |;'
exec_test 'echo bonjour | |'
exec_test 'echo bonjour >>> test'
exec_test 'echo bonjour > > out'
exec_test 'echo bonjour ; |'
exec_test '|'

# UNSET TEST
printf $YELLOW'UNSET TEST (l%d)\n'$RESET "$LINENO"

exec_test 'unset var'
exec_test 'unset sans arg'
exec_test 'unset PWD'
exec_test 'unset PATH ; ls'
exec_test 'unset PATH ; echo $PATH'
exec_test 'unset bla ; unset "$bla"'
#exec_test 'unset $var qui n'existe pas'
exec_test 'unset ='
exec_test 'unset "" test'
exec_test 'unset ""'

### TESTS ORIGINAUX (SOLALDUNCKEL) ###

## ECHO TESTS
#exec_test 'echo test tout'
#exec_test 'echo test      tout'
#exec_test 'echo -n test tout'
#exec_test 'echo -n -n -n test tout'
#
## CD TESTS
#exec_test 'cd .. ; pwd'
#exec_test 'cd /Users ; pwd'
#exec_test 'cd ; pwd'
#exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
#
## ENV EXPANSIONS + ESCAPE
#exec_test 'echo test     \    test'
#exec_test 'echo \"test'
#exec_test 'echo $TEST'
#exec_test 'echo "$TEST"'
#exec_test "echo '$TEST'"
#exec_test 'echo "$TEST$TEST$TEST"'
#exec_test 'echo "$TEST$TEST=lol$TEST"'
#exec_test 'echo "   $TEST lol $TEST"'
#exec_test 'echo $TEST$TEST$TEST'
#exec_test 'echo $TEST$TEST=lol$TEST""lol'
#exec_test 'echo    $TEST lol $TEST'
#exec_test 'echo test "" test "" test'
#exec_test 'echo "\$TEST"'
#exec_test 'echo "$=TEST"'
#exec_test 'echo "$"'
#exec_test 'echo "$?TEST"'
#exec_test 'echo $TEST $TEST'
#exec_test 'echo "$1TEST"'
#exec_test 'echo "$T1TEST"'
#
## ENV EXPANSIONS
#ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
#EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
#exec_test 'export ='
#exec_test 'export 1TEST= ;' $ENV_SHOW
exec_test 'export TEST ;' $EXPORT_SHOW
exec_test 'export ""="" ; ' $ENV_SHOW
#exec_test 'export TES=T="" ;' $ENV_SHOW
#exec_test 'export TE+S=T="" ;' $ENV_SHOW
#exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
#exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
#exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
#exec_test $ENV_SHOW
#exec_test $EXPORT_SHOW
exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

## REDIRECTIONS
exec_test 'echo test > ls ; cat ls'
exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
exec_test '> lol echo test lol; cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'
#
## MULTI TESTS
#exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'
#
## SYNTAX ERROR
#exec_test ';; test'
#exec_test '| test'
#exec_test 'echo > <'
#exec_test 'echo | |'
#exec_test '<'
#
## EXIT
#exec_test "exit 42"
#exec_test "exit 42 53 68"
#exec_test "exit 259"
#exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
#exec_test "exit 9223372036854775808"
#exec_test "exit -9223372036854775810"
#exec_test "exit -4"
#exec_test "exit 4 exit_trop_d_arg"
#exec_test "exit wrong"
#exec_test "exit wrong_command"
#exec_test "gdagadgag"
#exec_test "ls -Z"
#exec_test "cd gdhahahad"
#exec_test "ls -la | wtf"
#
## PIPE TESTS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test |cat -e|cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls'
#
#rm lol ls test
