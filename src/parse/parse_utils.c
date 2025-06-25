/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 01:18:51 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:47:19 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ps_is_whitespace(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (FAILURE);
	else
		return (SUCCESS);
}

size_t	ps_get_map_width(t_mapinfo *mapinfo, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(mapinfo->file[i]);
	while (mapinfo->file[i])
	{
		if (ft_strlen(mapinfo->file[i]) > biggest_len)
			biggest_len = ft_strlen(mapinfo->file[i]);
		i++;
	}
	return (biggest_len);
}
