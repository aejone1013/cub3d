/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:26:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/05/10 17:13:05 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <math.h>
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"

# define WIN_WIDTH 960
# define WIN_HEIGHT	720

# define MOVESPEED 0.0125
# define ROTSPEED 0.015

# define DIST_EDGE_MOUSE_WRAP 20

# define ERR_USAGE "ex: ./cub3d map.cub"
# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/sky RGB color"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid sky RGB color"
# define ERR_INVALID_MAP "Invalide map description"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture"
# define ERR_TEX_INVALID "Invalid texture"
# define ERR_COLOR_MISSING "Missing color"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (ex: N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

typedef enum e_output
{
    SUCCESS = 0,
    FAILURE = 1,
    ERR = 2,
    BREAK = 3,
    CONTINUE = 4
};

typedef enum e_texture
{
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3,
}	t_texture;

typedef struct s_img
{
    void	*img;
    int		*addr;
    int		pixel_bits;
    int		line_size;
    int		endian;
}	t_img;

typedef struct s_texinfo
{
    char			*img_north;
    char			*img_south;
    char			*img_west;
    char			*img_east;
    int				*floor;
    int				*sky;
    unsigned long	hex_floor;
    unsigned long	hex_sky;
    int				size;
    int				index;
    double			step;
    double			pos;
    int				x;
    int				y;
}	t_texinfo;

typedef struct s_player
{
    char	dir;
    double	pos_x;
    double	pos_y;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
    int		has_moved;
    int		move_x;
    int		move_y;
    int		rotate;
}	t_player;

typedef struct s_ray
{
    double	camera_x;
    double	dir_x;
    double	dir_y;
    int		map_x;
    int		map_y;
    int		step_x;
    int		step_y;
    double	side_x;
    double	side_y;
    double	delta_x;
    double	delta_y;
    double	wall_dist;
    double	wall_x;
    int		side;
    int		line_height;
    int		draw_start;
    int		draw_end;
}	t_ray;	

typedef struct s_mapinfo
{
    char		**file;
    int			fd;
    int			line_count;
    char		*path;
    int			height;
    int			width;
    int			index_end_of_map;
}	t_mapinfo;

typedef struct s_data
{
    void		*mlx;
    void		*win;
    int			win_height;
    int			win_width;
    t_mapinfo	mapinfo;
    t_img		img;
    char		**map;
    t_player	player;
    t_ray		ray;
    int			**texture_pixels;
    int			**textures;
    t_texinfo	texinfo;
}	t_data;

/* Function Prototypes */
void	rd_render_imgs(t_data *data);
void	init_ray(t_ray *ray);
void	rd_init_img(t_data *data, t_img *img, int width, int height);
int		malloc_free(t_data *data);
void	init_data(t_data *data, char *av);
void	read_map(t_data *data);
void	error(char *note, int error_code, t_data *data);
void	ft_free_2d(char **str);
void	check_line(char *line, t_data *data);
void	check_map(char **map, int i, t_data *data);
int		ft_isspace(char c);
char	*str_no_isspace(char *line, int start, int id_check);
void	put_rgb(char *line, int start, int id, t_data *data);
int		put_rgb_utils(char *path, t_data *data, int id);
int		check_extension(char *line);
int		set_xpm(t_data *data, char *temp, int id);
char	**ft_split_parsing(char const *s);
int		rd_render(t_data *data);
void	clean_exit(t_data *data, int code);
int		free_data(t_data *data);
void	free_tab(void **tab);
int		raycasting(t_player *player, t_data *data);
void	rd_update_tex_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);
void	rd_init_tex_pix(t_data *data);
int		player_move(t_data *data);
int		quit_cub3d(t_data *data);
void	input_handler(t_data *data);
int		rotate_player(t_data *data, double rotdir);
int		validate_move(t_data *data, double new_x, double new_y);
void	init_player_direction(t_data *data);

#endif
