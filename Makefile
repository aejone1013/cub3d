# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 20:36:57 by jaoh              #+#    #+#              #
#    Updated: 2025/04/20 17:56:12 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= cc

RM			= rm -rf

INCLUDE		= includes

MLX_DIR		= mlx

LIBFT_DIR	= libft

CFLAGS 		= -O3 -funroll-loops -std=c99 -Wall -Werror -Wextra -MMD -I${INCLUDE} -I${MLX_DIR} -I${LIBFT_DIR} -g

LDFLAGS 	= -L${MLX_DIR} -L${LIBFT_DIR} -lmlx -lXext -lX11 -lm -lbsd -lft

LIBFT		= ${LIBFT_DIR}/libft.a

MLX 		= ${MLX_DIR}/libmlx.a

SRC			 = main.c cub_utils.c check_map.c color_utils.c \
				parse_rgb.c read_map_utils.c read_map_utils2.c \
				read_map.c

SRC_DIR		= src/

OBJ_DIR		= obj/

SRCS 		= $(addprefix $(SRC_DIR), $(SRC))

OBJS		= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

OBJF		= .cache

DEP 		= ${OBJS:%.o=%.d}

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo -e "${NAME} compiled\n"

-include $(DEP)

all: $(NAME)

$(MLX):
	@make -C ${MLX_DIR}

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJF):	
	@mkdir -p $(OBJ_DIR)	

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@$(RM) $(OBJ_DIR)
	@$(RM) $(DEP)
	@echo -e ".o files cleaned\n"

fclean:	clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo -e "${NAME} cleaned\n"

re: fclean all

.PHONY: all clean fclean re
