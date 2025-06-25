/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:46:26 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:47:07 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rd_init_tex_pixels(t_data *data)
{
	int	i;

	if (data->tex_pixels)
		free_tab((void **)data->tex_pixels);
	data->tex_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pixels);
	if (!data->tex_pixels)
		ft_exit(data, err_msg(NULL, "Could not allocate memory", 1));
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pixels);
		if (!data->tex_pixels[i])
			ft_exit(data, err_msg(NULL, "Could not allocate memory", 1));
		i++;
	}
}

static void	rd_get_texture_idx(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.idx = W;
		else
			data->texinfo.idx = E;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.idx = S;
		else
			data->texinfo.idx = N;
	}
}

void	rd_update_tex_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	rd_get_texture_idx(data, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->idx][tex->size * tex->y + tex->x];
		if (tex->idx == N || tex->idx == E)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pixels[y][x] = color;
		y++;
	}
}
