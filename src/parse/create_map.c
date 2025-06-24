/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:18:33 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/24 19:42:18 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ps_count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	data->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

static int	ps_fill_map(t_mapinfo *mapinfo, char **map_tab, int idx)
{
	int		i;
	int		j;

	mapinfo->width = ps_get_biggest_len(mapinfo, idx);
	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, "Could not allocate memory", FAILURE));
		while (mapinfo->file[idx][j] && mapinfo->file[idx][j] != '\n')
		{
			map_tab[i][j] = mapinfo->file[idx][j];
			j++;
		}	
		while (j < mapinfo->width)
			map_tab[i][j++] = '\0';
		i++;
		idx++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

static int	ps_get_map_info(t_data *data, char **file, int i)
{
	data->mapinfo.height = ps_count_map_lines(data, file, i);
	data->map = malloc(sizeof(char *) * (data->mapinfo.height + 1));
	if (!data->map)
		return (err_msg(NULL, "Could not allocate memory", FAILURE));
	if (ps_fill_map(&data->mapinfo, data->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	ps_space_to_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
		|| data->map[i][j] == '\r'
		|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
			j++;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == ' '
				&& j != data->map[i][ft_strlen(data->map[i]) - 1])
				data->map[i][j] = '1';
		}
		i++;
	}
}

int	ps_create_map(t_data *data, char **file, int i)
{
	if (ps_get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	ps_space_to_wall(data);
	return (SUCCESS);
}
