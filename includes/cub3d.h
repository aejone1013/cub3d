/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:26:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/21 15:53:39 by jaoh             ###   ########.fr       */
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

# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

# define MOVESPEED 0.0125
# define ROTSPEED 0.015

# define DIST_EDGE_MOUSE_WRAP 20

# ifndef BONUS
#  define BONUS 1
# endif

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

# define ID_F			100
# define ID_C			101
# define ID_NO			102
# define ID_SO			103
# define ID_WE			104
# define ID_EA			105

typedef enum e_output
{
    SUCCESS = 0,
    FAILURE = 1,
    ERR = 2,
    BREAK = 3,
    CONTINUE = 4
}   t_output;

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
    int				index;
    double			step;
    double			pos;
    int				x;
    int				y;
}	t_texinfo;

typedef struct s_parsing
{
	int			fd; 				// 파일 디스크립터
	char		*file; 				// 읽은 파일 명
	int			endline; 			// 맵 파싱 때 제대로 모든 요소들이 있는 지 확인용
	char		*line; 				// 맵 파싱 떼, 맵을 스플릿하기 위해 파일 내용 저장하는 라인
	char		*temp;
	char		**file_content; 	// 스플릿 이후 반환된 배열
	char		*buff;
	char		player_character; 	// 플래이어가 어디를 바라보는 지 저장하는 변수
	int			check_sky;
	int			check_land;
}		t_parsing;

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
    char		*line; 				// 맵 파싱 떼, 맵을 스플릿하기 위해 파일 내용 저장하는 라인
	char		*temp;
	char		*buff;
}	t_mapinfo;

typedef struct s_data
{
    void		*mlx;
    void		*window;
    int			win_height;
    int			win_width;
    char		**map;
    int			**texture_pixels;
    int			**textures;
    t_player	player;
    t_mapinfo	mapinfo;
    t_texinfo	texinfo;
    t_img		minimap;
    t_ray		ray;
    t_parsing   parsing;
}	t_data;

/* init */
void	init_data(t_data *data, char *av);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_mlx(t_data *data);

/* move */
void	input_handler(t_data *data);
void	init_player_direction(t_data *data);
int     player_move(t_data *data);
int     validate_move(t_data *data, double new_x, double new_y);
int     rotate_player(t_data *data, double rotdir);

/* parse */
void	ft_free_2d(char **str);
int	    check_argv(char *argv);
void	error(char *note, int error_code, t_data *data);
int	    ft_isspace(char c);
char	*str_no_isspace(char *line, int start, int id_check);
int	    check_extension(char *line);
int	    set_xpm(t_data *data, char *temp, int id);
int	    put_rgb_utils(char *path, t_data *data, int id);
void	check_line(char *line, t_data *data);
void	check_map(char **map, int i, t_data *data);
char	**ft_split_parsing(char const *s);
void	put_rgb(char *line, int start, int id, t_data *data);
void	read_map(t_data *data);

/* render */
void	rd_set_image_pixel(t_img *img, int x, int y, int color);
void	rd_render_minimap(t_data *data);
void	rd_render_minimap_img(t_data *data, t_minimap *minimap);
int     rd_raycasting(t_player *player, t_data *data);
void	rd_render_imgs(t_data *data);
int     rd_render(t_data *data);
void	rd_init_tex_pix(t_data *data);
void	rd_update_tex_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* utils*/
void	free_tab(void **tab);
int	    free_data(t_data *data);
void	clean_exit(t_data *data, int code);
int	    quit_cub3d(t_data *data);
int	    err_msg(char *detail, char *str, int code);

#endif