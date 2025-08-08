# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhurtamo <mhurtamo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 19:38:50 by mhurtamo          #+#    #+#              #
#    Updated: 2025/02/16 20:01:25 by mhurtamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c arg_utils.c com_utils.c env_expansion.c free_functions.c line_validator.c make_args.c make_coms.c print_tokens.c random_utils.c token_validator.c str_utils.c tokenization.c token_utils.c
HEAD	= ./

OBJS	= ${SRCS:.c=.o}

NAME	= philo

RM	= rm -f

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -pthread

all:	${NAME}

c.o: ${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	
clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all clean

.PHONY:	all clean fclean re
