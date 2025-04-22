/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:26:45 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/20 17:56:08 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

typedef struct s_vec
{
	double	x;
	double	y;
	int		door;
}	t_vec;

typedef struct s_player
{
	t_vec	position;
	t_vec	direction;
	t_vec	camera;
}	t_player;

typedef struct s_ray
{
	t_vec	dir;
	int		side;
}	t_ray;	

typedef struct s_frame
{
	void			*img;
	char			*addr;
	int				f_height;
	int				f_width;
	int				bpp;
	int				ll;
	int				endian;
	struct s_frame	*next;
	struct s_frame	*prev;
}	t_frame;

#endif