make clean

echo "                                                    MANDATORY"
make philo

wait_for_keypress()
{
	read -n 1 -s -r -p "		Press any key to continue..."
	echo ""
}
check_dead()
{
	var="$1"
	echo -n "TEST $var   "
	output=$($var)
	if [ $(echo "$output" | grep died | wc -l) -eq 1 ]; then
		echo -e -n "	dead"
		valgrind_output=$(valgrind --trace-children=yes --track-origins=yes -s --child-silent-after-fork=yes $var 2>&1)
		if [ $(echo "$valgrind_output" | grep -c "All heap blocks were freed -- no leaks are possible") -eq 1 ]; then
			echo -e -n "	Heap	"
		else
			echo -e -n "Heap check: Failed		"
		fi
		if [ $(echo -e -n "$valgrind_output" | grep "ERROR SUMMARY: 0 errors from 0 contexts" | wc -l) -eq 1 ]; then
			echo -e -n "Valgrind	"
		else
			echo -e "Valgrind check: Errors found"
		fi
		echo  "$(echo "	$output" | grep died | grep -E -o 'died.*' )"
	else
		echo -e "		\033[41malive\033[0m"
		echo  "$(echo "	$output" | tail -n 1)"
	fi
}
check_alive()
{
	var="$1"
	echo -n "TEST $var   "
	output=$($var)
	if [ $(echo "$output" | grep died | wc -l) -eq 0 ]; then
		echo -e -n "	alive"
		valgrind_output=$(valgrind --trace-children=yes --track-origins=yes -s --child-silent-after-fork=yes $var 2>&1)
		if [ $(echo -e -n "$valgrind_output" | grep "All heap blocks were freed -- no leaks are possible" | wc -l) -eq 1 ]; then
			echo -e -n "	Heap	"
		else
			echo -e -n "Heap check: Failed		"
		fi
		if [ $(echo -e -n "$valgrind_output" | grep "ERROR SUMMARY: 0 errors from 0 contexts" | wc -l) -eq 1 ]; then
			echo -e "Valgrind"
		else
			echo -e "Valgrind check: Errors found"
		fi
	else
		echo -e "		\033[41mdead\033[0m"
		echo  "$(echo "	$output" | tail -n 1)"
	fi
}

check_dead	"philo/philo 1 800 200 200 99				"
check_alive	"philo/philo 2 800 200 200 99				"
check_alive	"philo/philo 5 400 100 100 99				"
check_alive	"philo/philo 5 800 200 200 7				"
check_alive	"philo/philo 4 410 200 200 99				"
check_dead	"philo/philo 4 310 200 100 99				"

check_dead	"philo/philo 5 410 200 200 99				"
check_dead	"philo/philo 5 310 200 100 99				"

check_dead	"philo/philo 4 310 200 100 99				"
check_dead	"philo/philo 9 410 200 200 99				"
check_alive	"philo/philo 8 410 200 200 99				"
check_alive	"philo/philo 5 800 200 200 99				"
check_alive	"philo/philo 4 410 200 200 99				"
check_dead	"philo/philo 2 60 60 60 99					"
check_dead	"philo/philo 6 7 28 1 99					"
check_dead	"philo/philo 6 10 40 2 99					"
check_dead	"philo/philo 6 12 48 3 99					"
check_dead	"philo/philo 6 15 60 4 99					"
check_dead	"philo/philo 7 7 28 1 99					"
check_dead	"philo/philo 7 10 40 2 99					"
check_dead	"philo/philo 7 12 48 3 99					"
check_dead	"philo/philo 7 15 60 4 99					"

echo "                                                    BONUS"
make bonus

check_dead	"philo_bonus/philo_bonus 1 800 200 200 99"
check_alive	"philo_bonus/philo_bonus 2 800 200 200 99"
check_alive	"philo_bonus/philo_bonus 5 400 100 100 99"
check_alive	"philo_bonus/philo_bonus 5 800 200 200 7	"
check_alive	"philo_bonus/philo_bonus 4 410 200 200 99"
check_dead	"philo_bonus/philo_bonus 4 310 200 100 99"

check_dead	"philo_bonus/philo_bonus 5 410 200 200 99"
check_dead	"philo_bonus/philo_bonus 5 310 200 100 99"

check_dead	"philo_bonus/philo_bonus 4 310 200 100 99	"
check_dead	"philo_bonus/philo_bonus 9 410 200 200 99	"
check_alive "philo_bonus/philo_bonus 8 410 200 200 99	"
check_alive "philo_bonus/philo_bonus 5 800 200 200 99	"
check_alive "philo_bonus/philo_bonus 4 410 200 200 99	"
check_dead	"philo_bonus/philo_bonus 2 60 60 60 99		"
check_dead	"philo_bonus/philo_bonus 6 7 28 1 99		"
check_dead	"philo_bonus/philo_bonus 6 10 40 2 99		"
check_dead	"philo_bonus/philo_bonus 6 12 48 3 99		"
check_dead	"philo_bonus/philo_bonus 6 15 60 4 99		"
check_dead	"philo_bonus/philo_bonus 7 7 28 1 99		"
check_dead	"philo_bonus/philo_bonus 7 10 40 2 99		"
check_dead	"philo_bonus/philo_bonus 7 12 48 3 99		"
check_dead	"philo_bonus/philo_bonus 7 15 60 4 99		"

make fclean

echo ""
norminette | grep -v OK
if [ $(norminette | grep -v OK | wc -l) -eq 0 ]; then
  echo "	Norminette sends its love!"
fi
