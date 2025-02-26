# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 15:07:00 by abessa-m          #+#    #+#              #
#    Updated: 2025/02/26 08:56:51 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo/philo
NAME-BONUS		:= philo_bonus/philo_bonus
##################################################################### Compiler #
CC				:= cc
CFLAGS			:= \
	-g -pthread \
	-Wall -Wextra -Werror 
########################################################### Intermidiate steps #
RM				:= rm -f
AR				:= ar rcs
########################################################## Objects and Headers #
HEADERS		:= philo.h philo_bonus.h
SRCS			:= \
	philo/main.c \
	philo/initialize.c philo/utils.c \
	philo/thread.c philo/thread-fork.c philo/thread-try.c
OBJS			:= $(SRCS:.c=.o)
SRCS-BONUS		:= \
	philo_bonus/main_bonus.c \
	philo_bonus/initialize_bonus.c philo_bonus/utils_bonus.c \
	philo_bonus/routine_bonus.c 
OBJS-BONUS		:= $(SRCS-BONUS:.c=.o)
###################################################################### Targets #
all: $(NAME) bonus

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

philo: $(NAME)

bonus: $(OBJS-BONUS)
	@$(CC) $(CFLAGS) $(OBJS-BONUS) -o $(NAME-BONUS)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@ \
	&& echo "$(GRAY)Compiled:$(COR) $<"

clean:
	@$(RM) *.o *.gch */*.o */*.gch \
	; echo "$(GRAY)cleaned sources$(COR)"

fclean: clean
	@$(RM) $(NAME) $(NAME-BONUS) \
	&& echo "$(GRAY)cleaned binaries$(COR)"

re: fclean all
	@echo "$(GRAY)redone$(COR)"

.PHONY: all clean fclean re
####################################################################### Colors #
COR		:= \033[0m# COlor Remove
PURPLE	:= \033[1;35m# purple
GRAY	:= \033[1;90m# gray
YELLOW	:= \033[1;93m# yellow
######################################################################### Test #
#Recomendation: alias t="make test"
#ARG-TEST	:= 200 62 60 60
ARG-TEST	:= 5 240 60 60 21

test: bonus
	@echo "$(YELLOW)	Checking for memory issues $(COR)" ; \
	valgrind --show-error-list=yes \
	--leak-check=full --show-leak-kinds=all --track-origins=yes \
	./philo_bonus/philo_bonus $(ARG-TEST) && \
	echo "$(COR)$(GRAY)Return value: $$?$(COR)" ; \
	sleep 1 ; \
	$(RM) */*.o */*.gch ;\
	echo -n "$(YELLOW)" ; \
	norminette | grep -v -E \
	"Too many functions in file|Comment is invalid in this scope|Empty line in \
	function|Consecutive newlines|Space on empty line" \
	| grep Error ; echo -n "$(COR)" \
	&& ./philo_bonus/philo_bonus 3 402 200 200 40


#For thread testing in the mandatory part
#echo "$(YELLOW)	Checking thread issues with helgrind $(COR)" ; \
#	sleep 1 ; \
#	valgrind  --quiet --show-error-list=yes \
#	--tool=helgrind \
#	./philo_bonus/philo_bonus $(ARG-TEST) && \
#echo "$(YELLOW)	Checking thread issues with DRD $(COR)" ; \
#	sleep 1 ; \
#	valgrind --quiet --show-error-list=yes \
#	--tool=drd \
#	./philo_bonus/philo_bonus $(ARG-TEST) && \