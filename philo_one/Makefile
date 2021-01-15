# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 18:30:23 by user42            #+#    #+#              #
#    Updated: 2021/01/15 13:19:36 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_one

SRCS_DIR = srcs/

SRCS =	philo_one.c		\
		threads.c		\
		actions.c		\
		precise_time.c	\
		utils.c

INCS = incs/philo_one.h

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