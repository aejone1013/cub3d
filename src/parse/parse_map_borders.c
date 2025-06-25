/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:17:59 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:25:40 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ps_check_top_or_bottom(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (FAILURE);
	while (map[i][j] == ' ' || map[i][j] == '\t'
	|| map[i][j] == '\r' || map[i][j] == '\v'
	|| map[i][j] == '\f')
		j++;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	ps_check_sides(t_mapinfo *mapinfo, char **map)
{
	int	i;
	int	j;

	if (ps_check_top_or_bottom(map, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (mapinfo->height - 1))
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (ps_check_top_or_bottom(map, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
