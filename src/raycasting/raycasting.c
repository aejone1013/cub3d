/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:09:44 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/20 16:45:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rc_rendering(t_data *data)
{
	int		x;
	double	cam_x;
	double	ray_dist;

	mlx_clear_window(data->mlx, data->window);
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		data->ray_dir.x = data->p_dir.x + data->p_cam.x * cam_x;
		data->ray_dir.y = data->p_dir.y + data->p_cam.y * cam_x;
		ray_dist = rc_raydist(&data->ray_dir, data);
		rc_stripe_pixel_put(data, x, ray_dist);
	}
	put_mini_map(data);
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->window, data->mini_map.img,
		MINI_MAP_X, MINI_MAP_Y);
	return (0);
}
