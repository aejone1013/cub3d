/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:10:35 by chanypar          #+#    #+#             */
/*   Updated: 2025/05/10 15:52:20 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*str_no_isspace(char *line, int start, int id_check)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = start + id_check;
	while (ft_isspace(line[i]))
		i++;
	if (i == 0)
		return (line);
	len = ft_strlen(line) - i;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}

int	check_extension(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len <= 4 || (!(line[len - 1] == 'm' && line[len - 2] == 'p' \
		&& line[len - 3] == 'x' && line[len - 4] == '.')))
		return (1);
	return (0);
}

int	set_xpm(t_data *data, char *temp, int id)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	data->textures[NORTH] = xpm_to_img(data, data->texinfo.img_north);
	data->textures[SOUTH] = xpm_to_img(data, data->texinfo.img_south);
	data->textures[EAST] = xpm_to_img(data, data->texinfo.img_east);
	data->textures[WEST] = xpm_to_img(data, data->texinfo.img_west);
}
