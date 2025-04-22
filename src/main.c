/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:48:39 by chanypar          #+#    #+#             */
/*   Updated: 2023/12/23 22:41:14 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	malloc_free(t_data *data)
{
    int	i;

    i = -1;
    ft_printf("window closed\n");
    while (data->map.map[++i])
        free(data->map.map[i]);
    free(data->map.map);
    mlx_destroy_window(data->mlx, data->window);
    mlx_destroy_image(data->mlx, data->img.img_north);
    mlx_destroy_image(data->mlx, data->img.img_south);
    mlx_destroy_image(data->mlx, data->img.img_east);
    mlx_destroy_image(data->mlx, data->img.img_west);
    free(data->mlx);
    exit(0);
    return (0);
}

void	start_game(t_data *data)
{
    mlx_loop_hook(data->mlx, rc_rendering, data);
    mlx_hook(data->window, KeyPress, KeyPressMask, &key_events, data);
    mlx_hook(data->window, DestroyNotify, StructureNotifyMask, &cleanup, data);
    mlx_hook(data->window, ButtonPress, ButtonPressMask, &mouse_press, data);
    mlx_hook(data->window, MotionNotify, PointerMotionMask, &mouse_move, data);
    mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
    t_data	data;

    if (ac != 2)
    {
        ft_printf("Error\nnote : this program takes one map.\n");
        exit(0);
    }
    init_data(&data, av[1]);
    read_map(&data);
    start_game(&data);
    return (0);
}
