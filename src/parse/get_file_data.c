/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:18:45 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:05:09 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ps_get_tex_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	ps_set_direction_tex(t_texinfo *textures, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		return (printf("%s", &line[j + 2]), ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->img_north))
		textures->img_north = ps_get_tex_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->img_south))
		textures->img_south = ps_get_tex_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->img_west))
		textures->img_west = ps_get_tex_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->img_east))
		textures->img_east = ps_get_tex_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

static int	ps_remove_whitespaces_get_info(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (map[i][j + 1] && ft_isprint(map[i][j + 1])
			&& !ft_isdigit(map[i][j]))
		{
			if (ps_set_direction_tex(&data->texinfo, map[i], j) == ERR)
				return (err_msg(data->mapinfo.path, "Invalid textures", FAILURE));
			return (BREAK);
		}	
		else
		{
			if (ps_set_tex_colors(data, &data->texinfo, map[i], j) == ERR)
				return (FAILURE);
			return (BREAK);
		}	
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (ps_create_map(data, map, i) == FAILURE)
			return (err_msg(data->mapinfo.path, "Invalid map description", FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	ps_get_file_data(t_data *data, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ps_remove_whitespaces_get_info(data, map, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
