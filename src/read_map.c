/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:50:19 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/23 09:25:36 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_real_map(char **map, int start, t_data *data)
{
	int	i;

	i = 0;
	data->map.map
		= malloc((data->parsing.endline - start + 1) * sizeof(char *));
	if (!data->map.map)
		error("malloc error", 1, data);
	while (map[start])
	{
		data->map.map[i] = malloc(ft_strlen(map[start]) + 1);
		if (!data->map.map[i])
		{
			ft_free_2d(data->map.map);
			error("malloc error", 1, data);
		}
		ft_strlcpy(data->map.map[i], map[start], ft_strlen(map[start]) + 1);
		i++;
		start++;
	}
	data->map.map[i] = NULL;
}

void	check_endline(char **map, t_parsing *p)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	p->endline = i;
}

void	check_file(char **map, t_data *data)
{
	int	i;

	i = -1;
	check_endline(map, &data->parsing);
	while (map[++i])
	{
		check_line(map[i], data);
		if (data->tex.tex_img[N]&& data->tex.tex_img[S] && data->tex.tex_img[E]
			&& data->tex.tex_img[W] && (data->parsing.check_land && data->parsing.check_sky))
		{
			i++;
			break ;
		}
	}
	if (!map[i])
		error("no id", 1, data);
	while (!ft_strchr(map[i], '1') && !ft_strchr(map[i], '0'))
		i++;
	if (!map[i])
		error("no map", 1, data);
	check_map(map, i, data);
	if (!data->parsing.player_caracter)
		error("player not exist", 1, data);
	create_real_map(map, i, data);
}

void	print_check(t_data *data)
{
	int		i;

	i = 0;
	printf("NO : %p\n", data->tex.tex_img[N]);
	printf("SO : %p\n", data->tex.tex_img[S]);
	printf("EA : %p\n", data->tex.tex_img[E]);
	printf("WE : %p\n", data->tex.tex_img[W]);
	printf("C : ");
	while (i < 3)
		printf("%d ", data->tex.floor[i++]);
	i = 0;
	printf("\nF : ");
	while (i < 3)
		printf("%d ", data->tex.sky[i++]);
	i = -1;
	printf("\n\nreal map start\n\n");
	while (data->map.map[++i])
		printf("%s\n", data->map.map[i]);
	printf("\n player position x : %f, y : %f\n", data->player.position.x, data->player.position.y);
	printf("player catacter : %c\n", data->parsing.player_caracter);
}

void	read_map(t_data *data)
{
	data->map.fd = open(data->map.path, O_RDONLY);
	if (data->map.fd <= 0)
		error("invalid fd", 0, data);
	data->parsing.line = malloc(1);
	if (!data->parsing.line)
		error("failed a malloc to line", 0, data);
	data->parsing.line[0] = '\0';
	data->parsing.buff = get_next_line(data->map.fd);
	while (data->parsing.buff)
	{
		data->parsing.temp = ft_strjoin(data->parsing.line, data->parsing.buff);
		free(data->parsing.line);
		free(data->parsing.buff);
		data->parsing.line = ft_strdup(data->parsing.temp);
		free(data->parsing.temp);
		data->parsing.buff = get_next_line(data->map.fd);
	}
	close(data->map.fd);
	data->parsing.file_content = ft_split_parsing(data->parsing.line);
	check_file(data->parsing.file_content, data);
	print_check(data);
	// ft_free_2d(data->parsing.file_content);
	error("no error", 1, data);
}