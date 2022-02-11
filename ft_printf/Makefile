# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 11:27:08 by vfiszbin          #+#    #+#              #
#    Updated: 2022/01/28 10:45:51 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/ft_printf.c\
		srcs/ft_printnbr_base.c\
		srcs/ft_printptr_base.c\
		srcs/ft_print_uint_fd.c\
		srcs/ft_printchar_fd.c\
		srcs/ft_printnbr_fd.c\
		srcs/ft_printstr_fd.c\

INCLUDES = -I./includes

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $ $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	${MAKE} -C ./libft
	cp libft/libft.a $(NAME)
	ar rc ${NAME} ${OBJS}

all: ${NAME}

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re