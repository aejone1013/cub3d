/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:16:52 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/24 19:31:25 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_img(t_data *data, t_img *image, int width, int height)
{
	init_img(image);
	image->img = mlx_new_image(data->mlx, width, height);
	if (image->img == NULL)
		ft_exit(data, err_msg("mlx", "Could not create mlx image", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_texture_img(t_data *data, t_img *image, char *path)
{
	init_img(image);
	image->img = mlx_xpm_file_to_image(data->mlx, path, &data->texinfo.size,
			&data->texinfo.size);
	if (image->img == NULL)
		ft_exit(data, err_msg("mlx", "Could not create mlx image", 1));
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
	return ;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_exit(data, err_msg("mlx", "Could not start mlx", 1));
	data->window = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->window)
		ft_exit(data, err_msg("mlx", "Could not create mlx window", 1));
	if (BONUS)
		mlx_mouse_move(data->mlx, data->window, data->win_width / 2,
			data->win_height / 2);
	return ;
}
