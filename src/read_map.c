/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:50:19 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/20 17:56:11 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_real_map(char **map, int start, t_data *data)
{
    int	i;

    i = 0;
    data->map.map = malloc((data->map.height - start + 1) * sizeof(char *));
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

void	check_endline(char **map, t_data *data)
{
    int	i;

    i = 0;
    while (map[i])
        i++;
    data->map.height = i;
}

void	check_file(char **map, t_data *data)
{
    int	i;

    i = -1;
    check_endline(map, data);
    while (map[++i])
    {
        check_line(map[i], data);
        if (data->img.img_north && data->img.img_south && data->img.img_west
            && data->img.img_east && (data->map.floor && data->map.sky))
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
    if (!data->player.position.x || !data->player.position.y)
        error("player not exist", 1, data);
    create_real_map(map, i, data);
}

void	print_check(t_data *data)
{
    int		i;

    i = 0;
    printf("NO : %p\n", data->img.img_north);
    printf("SO : %p\n", data->img.img_south);
    printf("EA : %p\n", data->img.img_east);
    printf("WE : %p\n", data->img.img_west);
    printf("C : ");
    while (i < 3)
        printf("%d ", (data->map.sky >> (16 - (i * 8))) & 0xFF);
    i = 0;
    printf("\nF : ");
    while (i < 3)
        printf("%d ", (data->map.floor >> (16 - (i * 8))) & 0xFF);
    i = -1;
    printf("\n\nreal map start\n\n");
    while (data->map.map[++i])
        printf("%s\n", data->map.map[i]);
}

void	read_map(t_data *data)
{
    data->map.fd = open(data->map.path, O_RDONLY);
    if (data->map.fd <= 0)
        error("invalid fd", 0, data);
    data->mapdata->line = malloc(1);
    if (!data->mapdata->line)
        error("failed a malloc to line", 0, data);
    data->mapdata->line[0] = '\0';
    data->mapdata->buff = get_next_line(data->map.fd);
    while (data->mapdata->buff)
    {
        data->mapdata->temp = ft_strjoin(data->mapdata->line, data->mapdata->buff);
        free(data->mapdata->line);
        free(data->mapdata->buff);
        data->mapdata->line = ft_strdup(data->mapdata->temp);
        free(data->mapdata->temp);
        data->mapdata->buff = get_next_line(data->map.fd);
    }
    close(data->map.fd);
    data->map.map = ft_split_parsing(data->mapdata->line);
    check_file(data->map.map, data);
    print_check(data);
    ft_free_2d(data->map.map);
    error("no error", 1, data);
}
