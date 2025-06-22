/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:13:39 by chanypar          #+#    #+#             */
/*   Updated: 2025/06/22 14:42:10 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_id(char *line, int i, int id, t_data *data) // 파싱 요소별 맞는 함수로 파싱
{
	char	*temp;
	int		rv;

	if (id == ID_NO || id == ID_SO || id == ID_WE || id == ID_EA)
	{
		if (check_extension(line)) // 동서남북 xpm extension 에러 체크, 없을 시 파싱
			error("not valid extension", 1, data);
		temp = str_no_isspace(line, i, 2); // isspace 제거
		if (!temp)
			error("no exist xpm file", 1, data);
		rv = set_xpm(data, temp, id); // xpm 파일을 이미지로 변환
		if (rv)
		{
			free(temp);
			if (rv == 1)
				error("not valid xpm file", 1, data);
			else if (rv == 2)
				error("double extension detected", 1, data);
		}
		free(temp);
	}
	else
		put_rgb(line, i, id, data); // rgb 값 에러 체크, 없을 시 파싱
}

void	check_line(char *line, t_data *data) // 맵의 한줄 에러 체크, 없을 시 파싱
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i])) // isspace 문자인 지 확인
		i++;
	if (!line[i])
		return ;
	if (line[i] == 'F')
		check_id(line, i, ID_F, data); // 파싱 요소별 맞는 함수로 파싱
	if (line[i] == 'C')
		check_id(line, i, ID_C, data); // 파싱 요소별 맞는 함수로 파싱
	if (line[i + 1] && line[i] == 'N' && line[i + 1] == 'O')
		check_id(line, i, ID_NO, data); // 파싱 요소별 맞는 함수로 파싱
	if (line[i + 1] && line[i] == 'S' && line[i + 1] == 'O')
		check_id(line, i, ID_SO, data); // 파싱 요소별 맞는 함수로 파싱
	if (line[i + 1] && line[i] == 'W' && line[i + 1] == 'E')
		check_id(line, i, ID_WE, data); // 파싱 요소별 맞는 함수로 파싱
	if (line[i + 1] && line[i] == 'E' && line[i + 1] == 'A')
		check_id(line, i, ID_EA, data); // 파싱 요소별 맞는 함수로 파싱
}

static void	check_player(char c, t_data *data) // 플래이어 문자 에러 확인, 없을 시 파싱
{
	if (ft_isspace(c))
		return ;
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		error("invalid caracter in map", 1, data);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (data->player.dir)
			error("player position twice", 1, data);
		data->player.dir = c;
	}
}

static void	check_empty(int i, int j, char **map, t_data *data) // 맵의 한줄이 비었는 지 확인
{
	if (!map[i][j])
		error("empty line in map", 1, data);
}

void	check_map(char **map, int i, t_data *data) // 맵 에러 체크 
{
	int		j;
	int		start;

	start = i--;
	while (map[++i])
	{
		j = 0;
		check_empty(i, j, map, data); // 맵의 한줄이 비었는 지 확인
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == start || i == data->parsing.endline)
					error("map not closed", 1, data);
				else if (j == 0 || j == (int)ft_strlen(map[i]) - 1)
					error("map not closed", 1, data);
				else if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					error("map not closed", 1, data);
				else if ((i != start && (int)ft_strlen(map[i - 1]) <= j)
					|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
					error("map not closed", 1, data);
			}
			check_player(map[i][j++], data); // 플래이어 문자 에러 확인, 없을 시 파싱
		}
	}
}
