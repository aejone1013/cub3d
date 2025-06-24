/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:05:20 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/23 15:41:10 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->texinfo.size * data->texinfo.size);
	if (!buffer)
		ft_exit(data, err_msg(NULL, "Could not allocate memory", 1));
	y = 0;
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	init_tex(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		ft_exit(data, err_msg(NULL, "Could not allocate memory", 1));
	data->textures[NORTH] = xpm_to_img(data, data->texinfo.img_north);
	data->textures[SOUTH] = xpm_to_img(data, data->texinfo.img_south);
	data->textures[EAST] = xpm_to_img(data, data->texinfo.img_east);
	data->textures[WEST] = xpm_to_img(data, data->texinfo.img_west);
}

void	init_texinfo(t_texinfo *textures)
{
	textures->img_north = NULL;
	textures->img_south = NULL;
	textures->img_west = NULL;
	textures->img_east = NULL;
	textures->floor = 0;
	textures->sky = 0;
	textures->hex_floor = 0x0;
	textures->hex_sky = 0x0;
	textures->size = 64;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}
