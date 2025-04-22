/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:15:11 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/20 17:56:09 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3d.h"
# define TEX_NB 7
# define TEX_PATHS 5

typedef enum e_parse_status
{
	MAP_OK,
	MAP_ERR,
	PANIC_ERR,
}	t_parse_status;

typedef enum e_texture
{
	N = 0,
	S = 1,
	E = 2,
	W = 3,
	D = 4,
}	t_texture;

typedef struct s_img
{
	void	*img;
    char	*pixel_data;
    int		pixel_bits;
    int		line_size;
	int		endian;
}	t_img;

typedef struct s_texdata
{
	void		*tex_img[TEX_PATHS];
	int			tex_h[TEX_PATHS];
	int			tex_w[TEX_PATHS];
	char		*tex_paths[TEX_PATHS];
	char		*tex_addr[TEX_PATHS];
	int			floor;
	int			sky;
	int			tex_nb;
}	t_texdata;

#endif