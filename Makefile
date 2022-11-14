# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 11:09:16 by aparedes          #+#    #+#              #
#    Updated: 2022/11/14 11:09:41 by aparedes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c \
		utils.c \
		check_and_init.c \

CFLAGS	= -Wall -Wextra -Werror
GCC	= gcc
RM	= rm -rf

OBJS	= $(SRCS:.c=.o)

%.o : %.c
	${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	$(GCC) $(CFLAGS) ${OBJS} -o $(NAME)

all:	$(NAME)

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	.o all norm clean fclean re
