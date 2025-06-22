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

#include "cub3d.h"

int	main(int ac, char **av)
{
    t_data	data;

    if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
    init_data(&data, av[1]);
    read_map(&data);
	rd_render_imgs(&data);
	input_handler(&data);
	mlx_loop_hook(data.mlx, rd_render, &data);
	mlx_loop(data.mlx);
	return (0);
}
