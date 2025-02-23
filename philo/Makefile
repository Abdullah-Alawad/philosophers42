NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra

T_FLAG = -pthread

RM = rm -f

MAIN_SRC = philo.c

MAIN_OBJ = ${MAIN_SRC:.c=.o}


all: ${NAME}

${NAME}: ${MAIN_OBJ}
		${CC} ${CFLAGS} ${T_FLAG} ${MAIN_SRC} -o ${NAME}

clean: ${MAIN_OBJ}
		rm -f ${MAIN_OBJ}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re