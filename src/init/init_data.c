/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:17:42 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/21 15:53:39 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data, char *av)
{
	init_mlx(data);
	if (check_argv(av))
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_printf("Error\nnote : not valid filename\n");
		exit(0);
	}
	data->parsing.file = av;
	data->parsing.endline = 0;
	data->texinfo.img_north = NULL;
	data->texinfo.img_south = NULL;
	data->texinfo.img_west = NULL;
	data->texinfo.img_east = NULL;
	data->parsing.player_character = '\0';
	data->parsing.check_land = 0;
	data->parsing.check_sky = 0;
	data->texinfo.floor = malloc(sizeof(int) * 3);
    data->texinfo.sky = malloc(sizeof(int) * 3);
    if (!data->texinfo.floor || !data->texinfo.sky)
        clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
    ft_memset(data->texinfo.floor, 0, sizeof(int) * 3);
    ft_memset(data->texinfo.sky, 0, sizeof(int) * 3);
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->line_size = 0;
	img->endian = 0;
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}