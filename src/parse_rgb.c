/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:46 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/22 16:52:00 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_rgb(char *line, int start, int id, t_data *data)
{
	char	*temp;

	temp = str_no_isspace(line, start, 1);
	if (!temp)
		error("malloc error", 1, data);
	if (put_rgb_utils(temp, data, id))
	{
		free(temp);
		error("rgb not valid number", 1, data);
	}
	free(temp);
}
