# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 18:18:43 by jaoh              #+#    #+#              #
#    Updated: 2024/08/01 18:18:43 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC 			= gcc

FLAGS 		= -Wall -Werror -Wextra

REMOVE 		= rm -f

SRCS 		= ft_isalpha.c 			\
			ft_isdigit.c 			\
			ft_isalnum.c 			\
			ft_isascii.c 			\
			ft_isprint.c 			\
			ft_strlen.c 			\
			ft_memset.c 			\
			ft_bzero.c 				\
			ft_memcpy.c 			\
			ft_memmove.c 			\
			ft_strlcpy.c 			\
			ft_strlcat.c 			\
			ft_toupper.c 			\
			ft_tolower.c 			\
			ft_strchr.c 			\
			ft_strrchr.c 			\
			ft_strncmp.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strnstr.c			\
			ft_atoi.c 				\
			ft_strdup.c 			\
			ft_calloc.c 			\
			ft_strnstr.c 			\
			ft_itoa.c 				\
			ft_substr.c	 			\
			ft_split.c 				\
			ft_strjoin.c 			\
			ft_strtrim.c			\
			ft_itoa.c 				\
			ft_strmapi.c 			\
			ft_striteri.c 			\
			ft_putchar_fd.c 		\
			ft_putstr_fd.c 			\
			ft_putendl_fd.c 		\
			ft_putnbr_fd.c			\
			ft_count_occurrences.c	\
			get_next_line.c			\
			ft_printf.c				\
			ft_argument_c.c			\
			ft_arguments_d_i.c		\
			ft_argument_p.c			\
			ft_argument_percent.c	\
			ft_argument_s.c			\
			ft_argument_u.c			\
			ft_arguments_x.c		\
			ft_print_reversed_str.c	\
			ft_free_ptr.c			\
			ft_hex_length.c			\
			ft_decimal_length.c		\
			ft_decimal_converter_to_hex.c \
			ft_lstnew.c	\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

OBJS 		= $(SRCS:.c=.o)

all:		${NAME}

${NAME}: 	${OBJS}
			@ar -rcs ${NAME} ${OBJS}

.c.o:
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:
			@${REMOVE} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			@${REMOVE} ${NAME}

.PHONY:		all clean fclean re