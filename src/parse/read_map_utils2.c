/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:12:30 by chanypar          #+#    #+#             */
/*   Updated: 2025/06/20 19:10:18 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_rgb_range(char *tmp) // 색 값 범위 확인
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (!(tmp[i] == ',' || tmp[i] == '\n'
				|| (tmp[i] >= '0' && tmp[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

static int	check_list_number(char **list) // 리스트가 숫자로만 구성이 되었는 지 확인
{
	int	i;
	int	j;

	i = 0;
	while (list[i])
	{
		j = 0;
		while (i == 0 && ft_isspace(list[i][j]))
			j++;
		while (list[i][j])
		{
			if (!ft_isdigit(list[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	checker_color(t_data *data, int id, int i) // 색이 제대로 저장이 되었고, 같은 데이터가 두번 입력됐는 지 확인
{
	if (id == ID_F && i == 3)
		data->parsing.check_land = 1;
	else if (id == ID_C && i == 3)
		data->parsing.check_sky = 1;
}

static int	put_rgb_to_param(t_data *data, char **list, int id) // 색 int형으로 변환 후 저장, 에러 확인
{
	int	i;

	i = 0;
	if (check_list_number(list)) // 리스트가 숫자로만 구성이 되었는 지 확인
		return (1);
	while (list[i] && i < 3)
	{
		if (id == ID_F)
		{
			data->texinfo.floor[i] = ft_atoi(list[i]);
			if (data->texinfo.floor[i] < 0 || data->texinfo.floor[i] > 255)
				return (1);
		}
		if (id == ID_C)
		{
			data->texinfo.sky[i] = ft_atoi(list[i]);
			if (data->texinfo.sky[i] < 0 || data->texinfo.sky[i] > 255)
				return (1);
		}
		i++;
	}
	checker_color(data, id, i); // 색이 제대로 저장이 되었고, 같은 데이터가 두번 입력됐는 지 확인
	return (0);
}

int	put_rgb_utils(char *path, t_data *data, int id) // rgb 값 에러 체크, 없을 시 파싱
{
	int		i;
	int		comma;
	char	**rgb_list;

	i = 0;
	comma = 0;
	while (path[i])
	{
		if (path[i] == ',')
			comma++;
		i++;
	}
	if (comma >= 3)
		return (1);
	rgb_list = ft_split(path, ','); // 3가지 색을 2차 배열로 변환
	if (!rgb_list)
		return (1);
	if (check_rgb_range(path)) // 색 값 범위 확인
		return (ft_free_2d(rgb_list), 1);
	if (put_rgb_to_param(data, rgb_list, id)) // 색 int형으로 변환 후 저장, 에러 확인
		return (ft_free_2d(rgb_list), 1);
	ft_free_2d(rgb_list);
	return (0);
}
