/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:01:59 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/20 19:52:03 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rd_set_image_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->line_size / 4) + x;
	img->addr[pixel] = color;
}
