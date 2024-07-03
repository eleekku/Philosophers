NAME = philo

SRCS = philo.c \
		philo_utils.c \
		philo_parsing.c \
		philo_routines.c \
		oversee.c

OBJS = $(SRCS:.c=.o)

MAKE = make

FLAGS = -Wall -Wextra -Werror

CC = cc

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${OBJS}: ${SRCS}
	${CC} ${FLAGS} -c ${SRCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re