/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:10:35 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/16 08:37:33 by chanypar         ###   ########.fr       */
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

int	set_xpm2(t_param *p, char *temp, int id)
{
	if (id == ID_WE)
	{
		if (p->img_west)
			return (2);
		p->img_west = mlx_xpm_file_to_image(p->mlx, temp, &p->img_w, &p->img_h);
		if (!p->img_west)
			return (1);
	}
	if (id == ID_EA)
	{
		if (p->img_east)
			return (2);
		p->img_east = mlx_xpm_file_to_image(p->mlx, temp, &p->img_w, &p->img_h);
		if (!p->img_east)
			return (1);
	}
	return (0);
}

int	set_xpm(t_param *p, char *temp, int id)
{
	if (id == ID_NO)
	{
		if (p->img_north)
			return (2);
		p->img_north
			= mlx_xpm_file_to_image(p->mlx, temp, &p->img_w, &p->img_h);
		if (!p->img_north)
			return (1);
	}
	if (id == ID_SO)
	{
		if (p->img_south)
			return (2);
		p->img_south
			= mlx_xpm_file_to_image(p->mlx, temp, &p->img_w, &p->img_h);
		if (!p->img_south)
			return (1);
	}
	return (set_xpm2(p, temp, id));
}
