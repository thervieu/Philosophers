# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 18:30:23 by user42            #+#    #+#              #
#    Updated: 2021/02/01 18:55:45 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

SRCS_DIR = srcs/

SRCS =	philo_two.c		\
		threads.c		\
		actions.c		\
		time_and_sem.c	\
		utils.c

INCS = incs/philo_two.h

OBJS_DIR = objs/

OBJ = $(SRCS:.c=.o)

OBJS = $(addprefix $(OBJS_DIR), $(OBJ))

FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCS) 
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling"
	@clang $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@clang -lpthread $(FLAGS) -o $(NAME) $(OBJS)
	@echo "Exec created !"

all: $(NAME)

clean:
	@echo "Removing objs"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Removing exec"
	@rm -f $(NAME)

re: fclean all