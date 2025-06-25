# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 20:36:57 by jaoh              #+#    #+#              #
#    Updated: 2025/06/25 14:46:45 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

BONUS 		= 0

CC			= cc

RM			= rm -rf

INCLUDE		= includes

MLX_DIR		= mlx

LIBFT_DIR	= libft

CFLAGS 		= -O3 -funroll-loops -std=c99 -Wall -Werror -Wextra -MMD -I${INCLUDE} -I${MLX_DIR} -I${LIBFT_DIR} -g

LDFLAGS 	= -L${MLX_DIR} -L${LIBFT_DIR} -lmlx -lXext -lX11 -lm -lbsd -lft

LIBFT		= ${LIBFT_DIR}/libft.a

MLX 		= ${MLX_DIR}/libmlx.a

SRC			= main.c
SRC_INIT	= init_data.c init_mlx.c init_tex.c
SRC_PARSE	= parse_arg.c parse_map_borders.c parse_map.c parse_tex.c \
				create_map.c fill_colors.c get_file_data.c parse.c parse_utils.c
SRC_PLAYER	= move.c rotate.c position.c direction.c input.c
SRC_RENDER	= image_utils.c minimap_image.c minimap_render.c raycasting.c render.c texture.c
SRC_UTILS	= utils1.c utils2.c

SRC_DIR		= src/
INIT_DIR	= src/init/
PARSE_DIR	= src/parse/
PLAYER_DIR	= src/player/
RENDER_DIR	= src/render/
UTILS_DIR	= src/utils/


SRCS 		=	$(addprefix $(SRC_DIR), $(SRC)) \
				$(addprefix $(INIT_DIR), $(SRC_INIT)) \
				$(addprefix $(PARSE_DIR), $(SRC_PARSE)) \
				$(addprefix $(PLAYER_DIR), $(SRC_PLAYER)) \
				$(addprefix $(RENDER_DIR), $(SRC_RENDER)) \
				$(addprefix $(UTILS_DIR), $(SRC_UTILS)) \

OBJ_DIR		= obj/

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

bonus:
	make all BONUS=1

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
