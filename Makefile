# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 20:36:57 by jaoh              #+#    #+#              #
#    Updated: 2025/06/20 20:17:19 by jaoh             ###   ########.fr        #
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

SRC			= main.c
SRC_RENDER	= image_utils.c minimap_image.c minimap_render.c raycasting.c render.c texture.c
SRC_MOVE	= p_move.c p_rotate.c p_position.c p_direction.c input_handler.c
SRC_UTILS	= utils.c
SRC_PARSE	= cub_utils.c read_map.c read_map_utils.c read_map_utils2.c \
				read_map_utils3.c read_map_utils4.c read_map_utils5.c
SRC_INIT	= init_data.c init_mlx.c

SRC_DIR		= src/
RENDER_DIR	= src/render/
MOVE_DIR	= src/move/
UTILS_DIR	= src/utils/
PARSE_DIR	= src/parse/
INIT_DIR	= src/init/


SRCS 		=	$(addprefix $(SRC_DIR), $(SRC)) \
				$(addprefix $(RENDER_DIR), $(SRC_RENDER)) \
				$(addprefix $(MOVE_DIR), $(SRC_MOVE)) \
				$(addprefix $(UTILS_DIR), $(SRC_UTILS)) \
				$(addprefix $(PARSE_DIR), $(SRC_PARSE)) \
				$(addprefix $(INIT_DIR), $(SRC_INIT)) 

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
