/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:46 by chanypar          #+#    #+#             */
/*   Updated: 2025/06/19 13:17:50 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_rgb(char *line, int start, int id, t_data *data) // rgb 값 에러 체크, 없을 시 파싱
{
	char	*temp;

	temp = str_no_isspace(line, start, 1); // isspace 제거
	if (!temp)
		error("malloc error", 1, data);
	if (put_rgb_utils(temp, data, id)) // rgb 값 에러 체크, 없을 시 파싱
	{
		free(temp);
		error("rgb not valid number", 1, data);
	}
	free(temp);
}
