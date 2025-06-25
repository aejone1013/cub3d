/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:18:29 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:47:21 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ps_check_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg_val(rgb[i], "Invalid RGB value (min: 0, max: 255)", FAILURE));
		i++;
	}
	return (SUCCESS);
}

static unsigned long	ps_rgbtohex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	ps_tex_is_valid(t_data *data, t_texinfo *textures)
{
	if (!textures->img_north || !textures->img_south || !textures->img_west
		|| !textures->img_east)
		return (err_msg(data->mapinfo.path, "Missing textures", FAILURE));
	if (!textures->floor || !textures->sky)
		return (err_msg(data->mapinfo.path, "Missing colors", FAILURE));
	if (ps_check_file(textures->img_north, false) == FAILURE
		|| ps_check_file(textures->img_south, false) == FAILURE
		|| ps_check_file(textures->img_west, false) == FAILURE
		|| ps_check_file(textures->img_east, false) == FAILURE
		|| ps_check_rgb(textures->floor) == FAILURE
		|| ps_check_rgb(textures->sky) == FAILURE)
		return (FAILURE);
	textures->hex_floor = ps_rgbtohex(textures->floor);
	textures->hex_sky = ps_rgbtohex(textures->sky);
	return (SUCCESS);
}
