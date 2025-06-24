/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:18:06 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 00:36:33 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ps_check_map_char(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	data->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
			|| data->map[i][j] == '\r'
			|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (err_msg(data->mapinfo.path, "Invalid character in map", FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir != '0')
				return (err_msg(data->mapinfo.path, "Map has more than one player", FAILURE));
			if (ft_strchr("NSEW", map_tab[i][j]) && data->player.dir == '0')
				data->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	ps_check_pos(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	i = (int)data->player.pos_y;
	j = (int)data->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| ps_is_whitespace(map_tab[i][j - 1]) == SUCCESS
		|| ps_is_whitespace(map_tab[i][j + 1]) == SUCCESS
		|| ps_is_whitespace(map_tab[i - 1][j]) == SUCCESS
		|| ps_is_whitespace(map_tab[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	ps_check_player_pos(t_data *data, char **map_tab)
{
	int	i;
	int	j;

	if (data->player.dir == '0')
		return (err_msg(data->mapinfo.path, "Map has no player position (expected N, S, E or W)", FAILURE));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (ps_check_pos(data, map_tab) == FAILURE)
		return (err_msg(data->mapinfo.path, "Invalid player position", FAILURE));
	return (SUCCESS);
}

static int	ps_check_end_of_map(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ps_map_is_valid(t_data *data, char **map_tab)
{
	if (!data->map)
		return (err_msg(data->mapinfo.path, "Missing map", FAILURE));
	if (ps_check_map_sides(&data->mapinfo, map_tab) == FAILURE)
		return (err_msg(data->mapinfo.path, "Map is not surrounded by walls", FAILURE));
	if (data->mapinfo.height < 3)
		return (err_msg(data->mapinfo.path, "Map is not at least 3 lines high", FAILURE));
	if (ps_check_map_char(data, map_tab) == FAILURE)
		return (FAILURE);
	if (ps_check_player_pos(data, map_tab) == FAILURE)
		return (FAILURE);
	if (ps_check_end_of_map(&data->mapinfo) == FAILURE)
		return (err_msg(data->mapinfo.path, "Map is not the last element in file", FAILURE));
	return (SUCCESS);
}
