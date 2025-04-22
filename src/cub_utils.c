/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanypar <chanypar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:17:25 by chanypar          #+#    #+#             */
/*   Updated: 2025/04/01 20:10:30 by chanypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_argv(char *argv)
{
	int		str;
	int		cnt;
	char	**tmp;

	tmp = ft_split(argv, '/');
	if (!tmp)
		ft_printf("Error\nnote : not valid fd\n");
	cnt = 0;
	while (tmp[cnt])
		cnt++;
	cnt--;
	str = ft_strlen(tmp[cnt]);
	if (str <= 4)
		return (ft_free_2d(tmp), 1);
	if (!(tmp[cnt][str - 1] == 'b' && \
		tmp[cnt][str - 2] == 'u' && \
		tmp[cnt][str - 3] == 'c' && \
		tmp[cnt][str - 4] == '.'))
		return (ft_free_2d(tmp), 1);
	return (ft_free_2d(tmp), 0);
}

void	init_data(t_data *data, char *av)
{
	data->mlx = mlx_init();
	if (check_argv(av))
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_printf("Error\nnote : not valid filename\n");
		exit(0);
	}
	data->map.path = av;
	data->pause = 0;
	data->img.img_north = NULL;
	data->img.img_south = NULL;
	data->img.img_west = NULL;
	data->img.img_east = NULL;
	data->player.position.x = 0;
	data->player.position.y = 0;
}

void	error(char *note, int error_code)
{
	t_data *data;
	
	if (error_code == 0)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_printf("Error\nnote : %s\n", note);
		exit(0);
	}
	if (data->img.img_south)
		mlx_destroy_image(data->mlx, data->img.img_south);
	if (data->img.img_east)
		mlx_destroy_image(data->mlx, data->img.img_east);
	if (data->img.img_west)
		mlx_destroy_image(data->mlx, data->img.img_west);
	if (data->img.img_north)
		mlx_destroy_image(data->mlx, data->img.img_north);
	ft_free_2d(data->map.map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_printf("Error\nnote : %s\n", note);
	exit(0);
}
