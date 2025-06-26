# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 20:36:57 by jaoh              #+#    #+#              #
#    Updated: 2025/06/26 18:05:49 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

BONUS 		= 0

CC			= cc

RM			= rm -rf

CFLAGS 		= -Werror -Wextra -Wall -g3

MLX_DIR		= mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_DIR)$(MLX_NAME)

LIBFT_DIR	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_DIR)$(LIBFT_NAME)

SRC			= main.c
SRC_INIT	= init_data.c init_mlx.c init_tex.c
SRC_PARSE	= parse_arg.c parse_map_borders.c parse_map.c parse_tex.c \
				create_map.c fill_colors.c get_file_data.c parse.c parse_utils.c
SRC_PLAYER	= move.c rotate.c position.c direction.c input.c
SRC_RENDER	= image_utils.c minimap_image.c minimap_render.c raycasting.c render.c texture.c
SRC_UTILS	= utils1.c utils2.c

SRC_DIR		= src/
INIT_DIR	= init/
PARSE_DIR	= parse/
PLAYER_DIR	= player/
RENDER_DIR	= render/
UTILS_DIR	= utils/


SRCS 		=	$(SRC) \
				$(addprefix $(INIT_DIR), $(SRC_INIT)) \
				$(addprefix $(PARSE_DIR), $(SRC_PARSE)) \
				$(addprefix $(PLAYER_DIR), $(SRC_PLAYER)) \
				$(addprefix $(RENDER_DIR), $(SRC_RENDER)) \
				$(addprefix $(UTILS_DIR), $(SRC_UTILS)) \

OBJ_DIR	= ./objs/
OBJ			= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))

INC			=	-I ./includes/ \
				-I ./libft/ \
				-I ./mlx/

all: $(OBJ_DIR) $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/init
	@mkdir -p $(OBJ_DIR)/parse
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/render
	@mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)


$(NAME):  $(OBJS)
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo -e "${NAME} compiled\n"


$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX):
	@make -sC $(MLX_DIR)

bonus:
	@make all BONUS=1

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo -e ".o files cleaned\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo -e "${NAME} cleaned\n"

re: fclean all

.PHONY: all clean fclean re bonus
