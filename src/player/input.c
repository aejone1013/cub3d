/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:55:07 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/24 19:55:22 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	p_key_press(int key, t_data *data)
{
	if (key == XK_Escape)
		exit_cub3d(data);
	if (key == XK_Left)
		data->player.rotate -= 1;
	if (key == XK_Right)
		data->player.rotate += 1;
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	return (0);
}

static int	p_key_release(int key, t_data *data)
{
	if (key == XK_Escape)
		exit_cub3d(data);
	if (key == XK_w && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == XK_s && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == XK_a && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == XK_d && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == XK_Left && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == XK_Right && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}

static void	p_wrap_mouse_pos(t_data *data, int x, int y)
{
	if (x > data->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->window, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = data->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->mlx, data->window, x, y);
	}
}

static int	p_mouse_motion(int x, int y, t_data *data)
{
	static int	old_x = WIN_WIDTH / 2;

	p_wrap_mouse_pos(data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		data->player.has_moved += p_rotate_player(data, -1);
	else if (x > old_x)
		data->player.has_moved += p_rotate_player(data, 1);
	old_x = x;
	return (0);
}

void	p_input_handler(t_data *data)
{
	mlx_hook(data->window, ClientMessage, NoEventMask, exit_cub3d, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, p_key_press, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, p_key_release, data);
	if (BONUS)
		mlx_hook(data->window, MotionNotify, PointerMotionMask,
			p_mouse_motion, data);
}
