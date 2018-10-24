#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysushkov <ysushkov@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 21:22:44 by ysushkov          #+#    #+#              #
#    Updated: 2018/10/24 11:05:09 by ysushkov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	avm

CC =	clang++

FLAGS =	-Wall -Wextra -Werror

#HEAD =	src/IOperand.hpp src/Operand.hpp src/mutantstack.hpp src/Factory.hpp

SRC =	src/main.cpp src/Parser.cpp src/Factory.cpp src/Operand.cpp
#src/Operand.cpp src/Factory.cpp

OBJ =	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
			@echo "\033[92mDONE\033[0m"
$(OBJ):		%.o: %.cpp
			$(CC) $(FLAGS) -c $< -o $@

clean:
			@/bin/rm -f $(OBJ)
			@echo "\033[92mObject files have been deleted\033[0m"
fclean:		clean
			@/bin/rm -f $(NAME)
			@echo "\033[92mExecutables have been deleted\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
