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

static int	parse_args(t_data *data, char **av)
{
	if (ps_check_file(av[1], true) == FAILURE)
		ft_exit(data, FAILURE);
	ps_parse(av[1], data);
	if (ps_get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (ps_map_is_valid(data, data->map) == FAILURE)
		return (free_data(data));
	if (ps_tex_is_valid(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	p_init_player_dir(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage: ", "./cub3d <path to map.cub>", 1));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	init_tex(&data);
	rd_render_img(&data);
	p_input_handler(&data);
	mlx_loop_hook(data.mlx, rd_render, &data);
	mlx_loop(data.mlx);
	return (0);
}
