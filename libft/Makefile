# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:22:20 by mminet            #+#    #+#              #
#    Updated: 2020/02/28 16:09:50 by mminet           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

vpath %c src

SRCS = 	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_strcut.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\

SRCSB = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

OBJSB = ${SRCSB:.c=.o}

HEADERS = libft.h

OBJS = ${SRCS:.c=.o}

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

all: 		${NAME}

bonus:		${OBJS} ${OBJSB}
			ar rcs ${NAME} ${OBJS} ${OBJSB}
			ranlib ${NAME}

$(OBJS):	${HEADERS}

$(NAME):	${OBJS}
			ar rcs ${NAME} ${OBJS}
			ranlib ${NAME}

%.c%.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

fclean: 	clean
			${RM} ${NAME}

clean:
			${RM} ${OBJS} ${OBJSB}

re:			fclean all

.PHONY:		all clean fclean re
