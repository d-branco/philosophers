make re
make clean

echo "                                                                   MANDATORY"
#sleep 1

wait_for_keypress()
{
	read -n 1 -s -r -p "		Press any key to continue..."
	echo ""
}
check_dead()
{
	var="$1"
	echo -n "Testing... $var"
	output=$($var)
	if [ $(echo "$output" | grep died | wc -l) -eq 1 ]; then
		echo -e -n "				dead"
#		echo  "$(echo "	$output" | tail -n 1)"
		valgrind_output=$(valgrind --trace-children=yes --track-origins=yes -s --child-silent-after-fork=yes $var 2>&1)
		if [ $(echo "$valgrind_output" | grep -c "All heap blocks were freed -- no leaks are possible") -eq 1 ]; then
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
		echo -e "		\033[41malive\033[0m"
		echo  "$(echo "	$output" | tail -n 1)"
	fi
}
check_alive()
{
	var="$1"
	echo -n "Testing... $var"
	output=$($var)
	if [ $(echo "$output" | grep died | wc -l) -eq 0 ]; then
		echo -e -n "				alive"
#		echo  "$(echo "	$output" | tail -n 1)"
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

check_dead	"philo/philo 1 800 200 200"
check_alive	"philo/philo 2 800 200 200 21"
check_alive	"philo/philo 5 400 100 100 21"
check_alive	"philo/philo 5 800 200 200 7"
check_alive	"philo/philo 4 410 200 200 21"
check_dead	"philo/philo 4 310 200 100 21"

#	The following test serve to check the time to die
#philo/philo 4 310 200 100 14
#echo "		FIM de philo/philo 4 310 200 100 14"
#wait_for_keypress
#philo/philo 4 410 200 200 21
#echo "		FIM de philo/philo 4 410 200 200"
#wait_for_keypress
#philo/philo 5 800 200 200 14
#echo "		FIM de philo/philo 5 800 200 200 14"
#wait_for_keypress
#philo/philo 4 410 200 200 14
#echo "		FIM de philo/philo 4 410 200 200 14"
#wait_for_keypress
#philo/philo 2  60  60  60 14
#echo "		FIM de philo/philo 2  60  60  60 14"
#wait_for_keypress
#philo/philo 10 410 200 200 14
#echo "		FIM de philo/philo 10 410 200 200 14"
#wait_for_keypress
#philo/philo 6 7 28 1 14
#echo "		FIM de philo/philo 6 7 28 1 14"
#wait_for_keypress
#philo/philo 6 10 40 2 14
#echo "		FIM de philo/philo 6 10 40 2 14"
#wait_for_keypress
#philo/philo 6 12 48 3 14
#echo "		FIM de philo/philo 6 12 48 3 14"
#wait_for_keypress
#philo/philo 6 15 60 4 14
#echo "		FIM de philo/philo 6 15 60 4 14"
#wait_for_keypress
#philo/philo 7 7 28 1 14
#echo "		FIM de philo/philo 7 7 28 1 14"
#wait_for_keypress
#philo/philo 7 10 40 2 14
#echo "		FIM de philo/philo 7 10 40 2 14"
#wait_for_keypress
#philo/philo 7 12 48 3 14
#echo "		FIM de philo/philo 7 12 48 3 14"
#wait_for_keypress
#philo/philo 7 15 60 4 14
#echo "		FIM de philo/philo 7 15 60 4 14"
#wait_for_keypress
#
echo "                                                                       BONUS"
#sleep 1

check_dead	"philo_bonus/philo_bonus 1 800 200 200 21"
check_alive	"philo_bonus/philo_bonus 2 800 200 200 21"
check_alive	"philo_bonus/philo_bonus 5 400 100 100 21"
check_alive	"philo_bonus/philo_bonus 5 800 200 200 7"
check_alive	"philo_bonus/philo_bonus 4 410 200 200 21"
check_dead	"philo_bonus/philo_bonus 4 310 200 100 21"

#	The following test serve to check the time to die
#philo_bonus/philo_bonus 4 310 200 100 14
#echo "		FIM de philo_bonus/philo_bonus 4 310 200 100 14"
#wait_for_keypress
#philo_bonus/philo_bonus 10 410 200 200 14
#echo "		FIM de philo_bonus/philo_bonus 10 410 200 200 14"
#wait_for_keypress
#philo_bonus/philo_bonus 5 800 200 200 14
#echo "		FIM de philo_bonus/philo_bonus 5 800 200 200 14"
#wait_for_keypress
#philo_bonus/philo_bonus 4 410 200 200 14
#echo "		FIM de philo_bonus/philo_bonus 4 410 200 200 14"
#wait_for_keypress
#philo_bonus/philo_bonus 2  60  60  60 14
#echo "		FIM de philo_bonus/philo_bonus 2  60  60  60 14"
#wait_for_keypress
#philo_bonus/philo_bonus 10 410 200 200 14
#echo "		FIM de philo_bonus/philo_bonus 10 410 200 200 14"
#wait_for_keypress
#philo_bonus/philo_bonus 6 7 28 1 14
#echo "		FIM de philo_bonus/philo_bonus 6 7 28 1 14"
#wait_for_keypress
#philo_bonus/philo_bonus 6 10 40 2 14
#echo "		FIM de philo_bonus/philo_bonus 6 10 40 2 14"
#wait_for_keypress
#philo_bonus/philo_bonus 6 12 48 3 14
#echo "		FIM de philo_bonus/philo_bonus 6 12 48 3 14"
#wait_for_keypress
#philo_bonus/philo_bonus 6 15 60 4 14
#echo "		FIM de philo_bonus/philo_bonus 6 15 60 4 14"
#wait_for_keypress
#philo_bonus/philo_bonus 7 7 28 1 14
#echo "		FIM de philo_bonus/philo_bonus 7 7 28 1 14"
#wait_for_keypress
#philo_bonus/philo_bonus 7 10 40 2 14
#echo "		FIM de philo_bonus/philo_bonus 7 10 40 2 14"
#wait_for_keypress
#philo_bonus/philo_bonus 7 12 48 3 14
#echo "		FIM de philo_bonus/philo_bonus 7 12 48 3 14"
#wait_for_keypress
#philo_bonus/philo_bonus 7 15 60 4 14
#echo "		FIM de philo_bonus/philo_bonus 7 15 60 4 14"

make fclean

echo ""
norminette | grep -v OK
if [ $(norminette | grep -v OK | wc -l) -eq 0 ]; then
  echo "	Norminette sends its love!"
fi
