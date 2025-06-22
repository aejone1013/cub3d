/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:40:03 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/20 20:12:16 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		rd_set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		rd_set_image_pixel(image, x, y, data->texinfo.hex_sky);
	else if (y < data->win_height -1)
		rd_set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static void	render_raycast(t_data *data)
{
	rd_init_tex_pix(data);
	init_ray(&data->ray);
	rd_raycasting(&data->player, data);
	render_frame(data);
}

void	rd_render_imgs(t_data *data)
{
	render_raycast(data);
	if (BONUS)
		rd_render_minimap(data);
}


int	rd_render(t_data *data)
{
	data->player.has_moved += player_move(data);
	if (data->player.has_moved == 0)
		return (0);
	rd_render_imgs(data);
	return (0);
}
