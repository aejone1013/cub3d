/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:12:30 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/22 18:25:30 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_rgb_range(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (!(tmp[i] == ',' || tmp[i] == '\n'
				|| (tmp[i] >= '0' && tmp[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

int	check_list_number(char **list)
{
	int	i;
	int	j;

	i = 0;
	while (list[i])
	{
		j = 0;
		while (i == 0 && ft_isspace(list[i][j]))
			j++;
		while (list[i][j])
		{
			if (!ft_isdigit(list[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	checker_color(int id, t_parsing *parsing, int i)
{
	if (id == ID_F && i == 3)
		parsing->check_land = 1;
	else if (id == ID_C && i == 3)
		parsing->check_sky = 1;
}

int	put_rgb_to_param(char **list, t_texdata *m_data, t_parsing *parsing, int id)
{
	int	i;

	i = 0;
	if (check_list_number(list))
		return (1);
	while (list[i] && i < 3)
	{
		if (id == ID_F)
		{
			m_data->floor[i] = ft_atoi(list[i]);
			if (m_data->floor[i] < 0 || m_data->floor[i] > 255)
				return (1);
		}
		if (id == ID_C)
		{
			m_data->sky[i] = ft_atoi(list[i]);
			if (m_data->sky[i] < 0 || m_data->sky[i] > 255)
				return (1);
		}
		i++;
	}
	checker_color(id, parsing, i);
	return (0);
}

int	put_rgb_utils(char *path, t_data *data, int id)
{
	int		i;
	int		comma;
	char	**rgb_list;

	i = 0;
	comma = 0;
	while (path[i])
	{
		if (path[i] == ',')
			comma++;
		i++;
	}
	if (comma >= 3)
		return (1);
	rgb_list = ft_split(path, ',');
	if (!rgb_list)
		return (1);
	if (check_rgb_range(path))
		return (ft_free_2d(rgb_list), 1);
	if (put_rgb_to_param(rgb_list, &data->tex, &data->parsing, id))
		return (ft_free_2d(rgb_list), 1);
	ft_free_2d(rgb_list);
	return (0);
}

