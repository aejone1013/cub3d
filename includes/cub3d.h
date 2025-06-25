/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:26:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/23 09:25:11 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ID_F			100
# define ID_C			101
# define ID_NO			102
# define ID_SO			103
# define ID_WE			104
# define ID_EA			105

# include <stdlib.h>
# include <stdio.h>
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
# include "render.h"
# include "parse.h"

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

// typedef enum e_keys
// {
// 	RIGHT = 65363,
// 	LEFT = 65361,
// 	UP = 65362,
// 	DOWN = 65364,
// 	ESC_KEY = 65307,
// 	SPACE_KEY = 32,
// 	W = 119,
// 	A = 97,
// 	S = 115,
// 	D = 100,
// 	R = 114,
// 	P = 112,
// 	M1 = 65307,
// }	t_keys;

typedef enum e_rot
{
	CLOCK,
	CCLOCK,
}	t_rot;

/*typedef enum e_move
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
}	t_move;*/

typedef struct s_wall
{
	int	height;
	int	draw_bounds[2];
	int	tex_pos[2];
}	t_wall;	

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		fd;
	char	*path;
}	t_map;

// typedef struct s_param
// {
// 	void		*img_north;
// 	void		*img_south;
// 	void		*img_east;
// 	void		*img_west;
// }		t_param;

typedef struct s_data
{
	t_map		map;
	t_parsing	parsing;
	t_img		img;
	// t_keys		keys;
	t_ray		ray;
	t_player	player;
	t_wall		wall;
	t_frame		frame;
	t_texdata	tex;
	// t_param		p;
	void		*mlx;
	void		*window;
}	t_data;


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

#endif
