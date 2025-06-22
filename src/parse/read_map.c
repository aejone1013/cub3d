/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:50:19 by chanypar          #+#    #+#             */
/*   Updated: 2025/06/22 13:57:38 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_real_map(char **map, int start, t_data *data) // mapdata.map에 맵 저장
{
	int	i;

	i = 0;
	data->map
		= malloc((data->parsing.endline - start + 1) * sizeof(char *));
	if (!data->map)
		error("malloc error", 1, data);
	while (map[start])
	{
		data->map[i] = malloc(ft_strlen(map[start]) + 1);
		if (!data->map[i])
		{
			free_tab((void**)data->map);
			error("malloc error", 1, data);
		}
		ft_strlcpy(data->map[i], map[start], ft_strlen(map[start]) + 1);
		i++;
		start++;
	}
	data->map[i] = NULL;
}

static void	check_endline(char **map, t_parsing *p) // 그져 파일이 몇 줄인지 확인 (파싱 때 필요)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	p->endline = i;
}

static void	check_file(char **map, t_data *data) // 파일 에러 확인 후, 없을 시 파싱
{
	int	i;

	i = -1;
	check_endline(map, &data->parsing); // 파일 줄 확인
	while (map[++i])
	{
		check_line(map[i], data); // 한줄 확인
		if (data->texinfo.img_north && data->texinfo.img_south && data->texinfo.img_west
			&& data->texinfo.img_east && (data->parsing.check_land && data->parsing.check_sky)) // 모든 값이 있을 시 break
		{
			i++;
			break ;
		}
	}
	if (!map[i]) // 이미지와 색이 전부 있지 않은 경우 에러처리
		error("no id", 1, data);
	while (!ft_strchr(map[i], '1') && !ft_strchr(map[i], '0')) // 맵의 시작점 찾기
		i++;
	if (!map[i])
		error("no map", 1, data);
	check_map(map, i, data); // 맵 에러 체크 
	if (!data->parsing.player_character) // 맵을 다 체크해도 플레이어 위치가 없을 경우
		error("player not exist", 1, data);
	create_real_map(map, i, data);  // mapdata.map에 맵 저장
}

static void	print_check(t_data *data) // 파싱값 출력함수
{
	int		i;

	i = 0;
	printf("NO : %p\n", data->texinfo.img_north);
	printf("SO : %p\n", data->texinfo.img_south);
	printf("EA : %p\n", data->texinfo.img_east);
	printf("WE : %p\n", data->texinfo.img_west);
	printf("C : ");
	while (i < 3)
		printf("%d ", data->texinfo.floor[i++]);
	i = 0;
	printf("\nF : ");
	while (i < 3)
		printf("%d ", data->texinfo.sky[i++]);
	i = -1;
	printf("\n\nreal map start\n\n");
	while (data->map[++i])
		printf("%s\n", data->map[i]);
}

void	read_map(t_data *data)
{
	data->parsing.fd = open(data->parsing.file, O_RDONLY);
	if (data->parsing.fd <= 0)
		error("invalid fd", 0, data);
	data->parsing.line = malloc(1);
	if (!data->parsing.line)
		error("failed a malloc to line", 0, data);
	data->parsing.line[0] = '\0';
	data->parsing.buff = get_next_line(data->parsing.fd);
	while (data->parsing.buff)
	{
		data->parsing.temp = ft_strjoin(data->parsing.line, data->parsing.buff);
		free(data->parsing.line);
		free(data->parsing.buff);
		data->parsing.line = ft_strdup(data->parsing.temp);
		free(data->parsing.temp);
		data->parsing.buff = get_next_line(data->parsing.fd);
	}
	close(data->parsing.fd);
	data->parsing.file_content = ft_split_parsing(data->parsing.line); // 읽은 파일을 2차배열로 저장 (개행문자 전부 살려서 저장)
	check_file(data->parsing.file_content, data); // 파일을 읽고, 에러가 없다면 파싱
	print_check(data); // 제대로 파싱이 되었는 지 확인
	free_tab((void**)data->map);
	error("no error", 1, data);
}
