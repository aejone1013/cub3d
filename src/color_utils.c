/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:12:30 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/16 08:37:33 by chanypar         ###   ########.fr       */
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

void	checker_color(int id, t_param *p, int i)
{
	if (id == ID_F && i == 3)
		p->check_land = 1;
	else if (id == ID_C && i == 3)
		p->check_sky = 1;
}

int	put_rgb_to_param(char **list, t_param *p, int id)
{
	int	i;

	i = 0;
	if (check_list_number(list))
		return (1);
	while (list[i] && i < 3)
	{
		if (id == ID_F)
		{
			p->land_color[i] = ft_atoi(list[i]);
			if (p->land_color[i] < 0 || p->land_color[i] > 255)
				return (1);
		}
		if (id == ID_C)
		{
			p->sky_color[i] = ft_atoi(list[i]);
			if (p->land_color[i] < 0 || p->land_color[i] > 255)
				return (1);
		}
		i++;
	}
	checker_color(id, p, i);
	return (0);
}

int	put_rgb_utils(char *path, t_param *p, int id)
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
	if (put_rgb_to_param(rgb_list, p, id))
		return (ft_free_2d(rgb_list), 1);
	ft_free_2d(rgb_list);
	return (0);
}
