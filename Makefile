# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 15:07:00 by abessa-m          #+#    #+#              #
#    Updated: 2025/02/21 15:20:22 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= philo/philo
##################################################################### Compiler #
CC				:= cc
CFLAGS			:= -pthread -g -Wall -Wextra
########################################################### Intermidiate steps #
RM				:= rm -f
AR				:= ar rcs
########################################################## Objects and Headers #
#HEADERS		:= philo.h
SRCS			:= \
	philo/main.c \
	philo/initialize.c philo/utils.c \
	philo/thread.c
OBJS			:= $(SRCS:.c=.o)
###################################################################### Targets #
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ \
	&& echo "$(GRAY)Compiled:$(COR) $(SRCS)"

clean:
	@$(RM) *.o *.gch \
	; echo "$(GRAY)cleaned sources$(COR)"

fclean: clean
	@$(RM) $(NAME) $(NAME-BONUS) \
	&& echo "$(GRAY)cleaned$(COR) $(NAME)"

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

test: all
	@echo -n "$(YELLOW)" ; \
	norminette | grep -v -E \
	"Too many functions in file|Comment is invalid in this scope" \
	| grep Error ; echo -n "$(COR)" ; \
	echo "$(YELLOW)	Checking for memory issues $(COR)" ; \
	valgrind --show-error-list=yes \
	--leak-check=full --show-leak-kinds=all --track-origins=yes \
	./philo/philo $(ARG-TEST) && \
	echo "$(YELLOW)	Checking thread issues with helgrind $(COR)" ; \
	valgrind --show-error-list=yes \
	--tool=helgrind \
	./philo/philo $(ARG-TEST) && \
	echo "$(YELLOW)	Checking thread issues with DRD $(COR)" ; \
	valgrind --show-error-list=yes \
	--tool=drd \
	./philo/philo $(ARG-TEST) && \
	echo "$(GRAY)Return value: $$?$(COR)" ; \
	$(RM) *.o *.gch
