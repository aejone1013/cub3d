/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:53:28 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 00:35:56 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	p_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVESPEED;
	return (p_confirm_move(data, new_x, new_y));
}

static int	p_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVESPEED;
	return (p_confirm_move(data, new_x, new_y));
}

static int	p_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * MOVESPEED;
	new_y = data->player.pos_y - data->player.dir_x * MOVESPEED;
	return (p_confirm_move(data, new_x, new_y));
}

static int	p_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * MOVESPEED;
	new_y = data->player.pos_y + data->player.dir_x * MOVESPEED;
	return (p_confirm_move(data, new_x, new_y));
}

int	p_player_move(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += p_forward(data);
	if (data->player.move_y == -1)
		moved += p_backward(data);
	if (data->player.move_x == -1)
		moved += p_left(data);
	if (data->player.move_x == 1)
		moved += p_right(data);
	if (data->player.rotate != 0)
		moved += p_rotate_player(data, data->player.rotate);
	return (moved);
}
