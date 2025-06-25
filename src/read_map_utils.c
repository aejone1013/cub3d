/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:10:35 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/22 20:04:50 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	set_xpm2(t_data *data, char *temp, int id)
{
	if (id == ID_WE)
	{
		if (data->tex.tex_img[W])
			return (2);
		data->tex.tex_img[W] = mlx_xpm_file_to_image(data->mlx, temp, &data->map.width, &data->map.height);
		if (!data->tex.tex_img[W])
			return (1);
	}
	if (id == ID_EA)
	{
		if (data->tex.tex_img[E])
			return (2);
		data->tex.tex_img[E] = mlx_xpm_file_to_image(data->mlx, temp, &data->map.width, &data->map.height);
		if (!data->tex.tex_img[E])
			return (1);
	}
	return (0);
}

int	set_xpm(t_data *data, char *temp, int id)
{
	if (id == ID_NO)
	{
		if (data->tex.tex_img[N])
			return (2);
		data->tex.tex_img[N]
			= mlx_xpm_file_to_image(data->mlx, temp, &data->map.width, &data->map.height);
		if (!data->tex.tex_img[N])
			return (1);
	}
	if (id == ID_SO)
	{
		if (data->tex.tex_img[S])
			return (2);
		data->tex.tex_img[S]
			= mlx_xpm_file_to_image(data->mlx, temp, &data->map.width, &data->map.height);
		if (!data->tex.tex_img[S])
			return (1);
	}
	return (set_xpm2(data, temp, id));
}
