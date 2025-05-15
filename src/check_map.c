/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:13:39 by chanypar          #+#    #+#             */
/*   Updated: 2025/05/09 11:13:02 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_id(char *line, int i, int id, t_data *data)
{
	char	*temp;
	int		rv;

	if (id == ID_NO || id == ID_SO || id == ID_WE || id == ID_EA)
	{
		if (check_extension(line))
			error("not valid extension", 1, data);
		temp = str_no_isspace(line, i, 2);
		if (!temp)
			error("no exist xpm file", 1, data);
		rv = set_xpm(data, temp, id);
		if (rv)
		{
			free(temp);
			if (rv == 1)
				error("not valid xpm file", 1, data);
			else if (rv == 2)
				error("double extension detected", 1, data);
		}
		free(temp);
	}
	else
		put_rgb(line, i, id, data);
}

void	check_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return ;
	if (line[i] == 'F')
		check_id(line, i, ID_F, data);
	if (line[i] == 'C')
		check_id(line, i, ID_C, data);
	if (line[i + 1] && line[i] == 'N' && line[i + 1] == 'O')
		check_id(line, i, ID_NO, data);
	if (line[i + 1] && line[i] == 'S' && line[i + 1] == 'O')
		check_id(line, i, ID_SO, data);
	if (line[i + 1] && line[i] == 'W' && line[i + 1] == 'E')
		check_id(line, i, ID_WE, data);
	if (line[i + 1] && line[i] == 'E' && line[i + 1] == 'A')
		check_id(line, i, ID_EA, data);
}

void	check_player(char c, t_data *data)
{
	if (ft_isspace(c))
		return ;
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		error("invalid caracter in map", 1, data);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (data->player)
			error("player position twice", 1, data);
		data->player = c;
	}
}

void	check_empty(int i, int j, char **map, t_data *data)
{
	if (!map[i][j])
		error("empty line in map", 1, data);
}

void	check_map(char **map, int i, t_data *data)
{
	int		j;
	int		start;

	start = i--;
	while (map[++i])
	{
		j = 0;
		check_empty(i, j, map, data);
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == start || i == data->endline)
					error("map not closed", 1, data);
				else if (j == 0 || j == (int)ft_strlen(map[i]) - 1)
					error("map not closed", 1, data);
				else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					error("map not closed", 1, data);
				else if ((i != start && (int)ft_strlen(map[i - 1]) <= j)
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					error("map not closed", 1, data);
			}
			check_player(map[i][j++], data);
		}
	}
}
