# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalfahal <aalfahal@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:14:21 by aalfahal          #+#    #+#              #
#    Updated: 2023/03/26 06:10:21 by aalfahal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	philo

SRC		=	SRC/philo.c			\
			SRC/philo_utils.c	\
			SRC/philo_utils2.c	\
			SRC/philo_life.c

SRCS	=	$(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -lpthread -o $(NAME)
clean:
	rm -fr $(SRCS)

fclean: clean
	rm -fr $(NAME)

re: fclean all