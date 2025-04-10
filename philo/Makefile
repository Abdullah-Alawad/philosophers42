# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalawad <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 14:14:56 by aalawad           #+#    #+#              #
#    Updated: 2025/03/13 14:14:58 by aalawad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

RM = rm -f

SRCS = utils.c init_table.c routine.c clean_n_errs.c \
		controller.c utils2.c

MAIN_SRC = philo.c

OBJS = ${SRCS:.c=.o}

MAIN_OBJ = philo.o

%.o:%.c philo.h
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${MAIN_OBJ} ${OBJS}
		${CC} ${CFLAGS} ${OBJS} ${MAIN_SRC} -o ${NAME}

clean:
		rm -f ${MAIN_OBJ} ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
