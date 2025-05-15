/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:50:19 by chanypar          #+#    #+#             */
/*   Updated: 2025/05/10 15:44:25 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_real_map(char **map, int start, t_data *data)
{
    int	i;

    i = 0;
    data->map = malloc((data->mapinfo.height - start + 1) * sizeof(char *));
    if (!data->map)
        error("malloc error", 1, data);
    while (map[start] && i < (data->mapinfo.height - start))
    {
        data->mapinfo.map[i] = malloc(ft_strlen(map[start]) + 1);
        if (!data->mapinfo.map[i])
        {
            ft_free_2d(data->mapinfo.map);
            error("malloc error", 1, data);
        }
        ft_strlcpy(data->mapinfo.map[i], map[start], ft_strlen(map[start]) + 1);
        i++;
        start++;
    }
    data->mapinfo.map[i] = NULL;
}

void	check_endline(char **map, t_data *data)
{
    int	i;

    i = 0;
    while (map[i])
        i++;
    data->mapinfo.height = i;
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
            && data->img.img_east && (data->mapinfo.floor && data->mapinfo.sky))
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
    printf("NO : %p\n", data->texinfo.img_north);
    printf("SO : %p\n", data->texinfo.img_south);
    printf("EA : %p\n", data->texinfo.img_east);
    printf("WE : %p\n", data->texinfo.img_west);
    printf("C : ");
    while (i < 3)
        printf("%d ", (data->texinfo.sky >> (16 - (i * 8))) & 0xFF);
    i = 0;
    printf("\nF : ");
    while (i < 3)
        printf("%d ", (data->texinfo.floor >> (16 - (i * 8))) & 0xFF);
    i = -1;
    printf("\n\nreal map start\n\n");
    while (data->mapinfo.map[++i])
        printf("%s\n", data->mapinfo.map[i]);
}

void	read_map(t_data *data)
{
    data->mapinfo.fd = open(data->mapinfo.path, O_RDONLY);
    if (data->mapinfo.fd <= 0)
        error("invalid fd", 0, data);
    data->mapinfo->line = malloc(1);
    if (!data->mapinfo->line)
        error("failed a malloc to line", 0, data);
    data->mapinfo->line[0] = '\0';
    data->mapinfo->buff = get_next_line(data->mapinfo.fd);
    while (data->mapinfo->buff)
    {
        data->mapinfo->temp = ft_strjoin(data->mapinfo->line, data->mapinfo->buff);
        free(data->mapinfo->line);
        free(data->mapinfo->buff);
        data->mapinfo->line = ft_strdup(data->mapinfo->temp);
        free(data->mapinfo->temp);
        data->mapinfo->buff = get_next_line(data->mapinfo.fd);
    }
    close(data->mapinfo.fd);
    data->mapinfo.map = ft_split_parsing(data->mapinfo->line);
    check_file(data->mapinfo.file, data);
    print_check(data);
    ft_free_2d(data->mapinfo.file);
    error("no error", 1, data);
}
