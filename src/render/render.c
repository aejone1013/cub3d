/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:40:03 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:47:05 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rd_set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex_pixels[y][x] > 0)
		rd_set_image_pixel(image, x, y, data->tex_pixels[y][x]);
	else if (y < data->win_height / 2)
		rd_set_image_pixel(image, x, y, data->texinfo.hex_sky);
	else if (y < data->win_height -1)
		rd_set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	rd_render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_mlx_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			rd_set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static void	rd_render_raycast(t_data *data)
{
	rd_init_tex_pixels(data);
	init_ray(&data->ray);
	rd_raycasting(&data->player, data);
	rd_render_frame(data);
}

void	rd_render_img(t_data *data)
{
	rd_render_raycast(data);
	if (BONUS)
		rd_render_minimap(data);
}

int	rd_render(t_data *data)
{
	data->player.has_moved += p_player_move(data);
	if (data->player.has_moved == 0)
		return (0);
	rd_render_img(data);
	return (0);
}
