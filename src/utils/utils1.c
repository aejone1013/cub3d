/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:53:13 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/24 20:10:38 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_texinfo(t_texinfo *texinfo)
{
	if (texinfo->img_north)
		free(texinfo->img_north);
	if (texinfo->img_south)
		free(texinfo->img_south);
	if (texinfo->img_west)
		free(texinfo->img_west);
	if (texinfo->img_east)
		free(texinfo->img_east);
	if (texinfo->floor)
		free(texinfo->floor);
	if (texinfo->sky)
		free(texinfo->sky);
}

static void	free_map(t_data *data)
{
	if (data->mapinfo.fd > 0)
		close(data->mapinfo.fd);
	if (data->mapinfo.file)
		free_tab((void **)data->mapinfo.file);
	if (data->map)
		free_tab((void **)data->map);
}

int	free_data(t_data *data)
{
	if (data->textures)
		free_tab((void **)data->textures);
	if (data->tex_pixels)
		free_tab((void **)data->tex_pixels);
	free_texinfo(&data->texinfo);
	free_map(data);
	return (FAILURE);
}
