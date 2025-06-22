/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:10:35 by chanypar          #+#    #+#             */
/*   Updated: 2025/06/20 19:08:39 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c) // isspace 문자 확인
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*str_no_isspace(char *line, int start, int id_check) // isspace 제거
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

int	check_extension(char *line) // 파일이 ".xpm"으로 확장자가 되어있는 지 확인
{
	int	len;

	len = ft_strlen(line);
	if (len <= 4 || (!(line[len - 1] == 'm' && line[len - 2] == 'p' \
		&& line[len - 3] == 'x' && line[len - 4] == '.')))
		return (1);
	return (0);
}

static int	set_xpm2(t_data *data, char *temp, int id) // xpm 파일을 이미지로 변환
{
	if (id == ID_WE)
	{
		if (data->texinfo.img_west)
			return (2);
		data->texinfo.img_west = mlx_xpm_file_to_image(data->mlx, temp, &data->win_width, &data->win_height);
		if (!data->texinfo.img_west)
			return (1);
	}
	if (id == ID_EA)
	{
		if (data->texinfo.img_east)
			return (2);
		data->texinfo.img_east = mlx_xpm_file_to_image(data->mlx, temp, &data->win_width, &data->win_height);
		if (!data->texinfo.img_east)
			return (1);
	}
	return (0);
}

int	set_xpm(t_data *data, char *temp, int id) // xpm 파일을 이미지로 변환
{
	if (id == ID_NO)
	{
		if (data->texinfo.img_north)
			return (2);
		data->texinfo.img_north
			= mlx_xpm_file_to_image(data->mlx, temp, &data->win_width, &data->win_height);
		if (!data->texinfo.img_north)
			return (1);
	}
	if (id == ID_SO)
	{
		if (data->texinfo.img_south)
			return (2);
		data->texinfo.img_south
			= mlx_xpm_file_to_image(data->mlx, temp, &data->win_width, &data->win_height);
		if (!data->texinfo.img_south)
			return (1);
	}
	return (set_xpm2(data, temp, id)); // xpm 파일을 이미지로 변환
}
