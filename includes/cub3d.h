/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:26:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/24 20:54:32 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

# ifndef DEBUG_MSG
#  define DEBUG_MSG 0
# endif

# ifndef MMAP_DEBUG_MSG
#  define MMAP_DEBUG_MSG 0
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define WIN_WIDTH 960
# define WIN_HEIGHT 720
# define MMAP_SIZE 128
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040
# define MOVESPEED 0.0125
# define ROTSPEED 0.015
# define DIST_EDGE_MOUSE_WRAP 20

enum e_output
{
    SUCCESS = 0,
    FAILURE = 1,
    ERR = 2,
    BREAK = 3,
    CONTINUE = 4
};

enum e_texture
{
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3,
};

typedef unsigned long	t_ulong;

typedef struct s_img
{
    void	*img;
    int		*addr;
    int		pixel_bits;
    int		size_line;
    int		endian;
}	t_img;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

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
    int				idx;
    double			step;
    double			pos;
    int				x;
    int				y;
}	t_texinfo;

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
    int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

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

typedef struct s_data
{
    void		*mlx;
    void		*window;
    int			win_height;
    int			win_width;
    char		**map;
    int			**tex_pixels;
    int			**textures;
    t_mapinfo	mapinfo;
	t_player	player;
	t_ray		ray;
	t_texinfo	texinfo;
	t_img		minimap;
}	t_data; 

/* init */
void	init_data(t_data *data);
void	init_img(t_img *img);
void	init_ray(t_ray *ray);
void	init_mlx_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_mlx(t_data *data);
void	init_tex(t_data *data);
void	init_texinfo(t_texinfo *texinfo);

/* parse */
int		ps_check_file(char *arg, bool cub);
void	ps_parse(char *path, t_data *data);
int		ps_get_file_data(t_data *data, char **map);
int		ps_set_tex_colors(t_data *data, t_texinfo *texinfo,
		char *line, int j);
int		ps_create_map(t_data *data, char **map, int i);
int		ps_tex_is_valid(t_data *data, t_texinfo *texinfo);
int		ps_map_is_valid(t_data *data, char **map_tab);
int		ps_check_map_sides(t_mapinfo *map, char **map_tab);
int		ps_is_whitespace(char c);
size_t	ps_get_biggest_len(t_mapinfo *map, int i);

/* render */
void	rd_set_image_pixel(t_img *img, int x, int y, int color);
void	rd_render_minimap(t_data *data);
void	rd_render_minimap_img(t_data *data, t_minimap *minimap);
int     rd_raycasting(t_player *player, t_data *data);
void	rd_render_img(t_data *data);
int     rd_render(t_data *data);
void	rd_init_tex_pixels(t_data *data);
void	rd_update_tex_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* player */
void	p_input_handler(t_data *data);
void	p_init_player_dir(t_data *data);
int     p_player_move(t_data *data);
int     p_confirm_move(t_data *data, double new_x, double new_y);
int     p_rotate_player(t_data *data, double rotdir);

/* utils*/
void	free_tab(void **tab);
int	    free_data(t_data *data);
void	ft_exit(t_data *data, int code);
int	    exit_cub3d(t_data *data);
int	    err_msg(char *detail, char *str, int code);
int     err_msg_val(int detail, char *str, int code);

/* debug */
void	debug_display_data(t_data *data);
void	debug_display_minimap(t_minimap *minimap);
void	debug_display_player(t_data *data);
void	debug_print_char_tab(char **tab);

#endif