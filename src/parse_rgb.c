/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:46 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/16 08:37:33 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_rgb(char *line, int start, int id, t_param *p)
{
	char	*temp;

	temp = str_no_isspace(line, start, 1);
	if (!temp)
		error("malloc error", 1, p);
	if (put_rgb_utils(temp, p, id))
	{
		free(temp);
		error("rgb not valid number", 1, p);
	}
	free(temp);
}
