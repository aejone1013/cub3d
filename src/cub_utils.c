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
	int	i;

	i = -1;
	data->mlx = mlx_init();
	if (check_argv(av))
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_printf("Error\nnote : not valid filename\n");
		exit(0);
	}
	data->map.path = av;
	while (++i < 4)
		data->tex.tex_img[i] = NULL;
	data->parsing.check_land = 0;
	data->parsing.check_sky = 0;
	data->parsing.player_caracter = '\0';
	ft_memset(data->tex.floor, 0, sizeof(data->tex.floor));
	ft_memset(data->tex.sky, 0, sizeof(data->tex.sky));
	data->player.position.x = 0;
	data->player.position.y = 0;
}

void	error(char *note, int error_code, t_data *data)
{
	if (!error_code)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_printf("Error\nnote : %s\n", note);
		exit(0);
	}
	if (data->tex.tex_img[N])
		mlx_destroy_image(data->mlx, data->tex.tex_img[N]);
	if (data->tex.tex_img[S])
		mlx_destroy_image(data->mlx, data->tex.tex_img[S]);
	if (data->tex.tex_img[E])
		mlx_destroy_image(data->mlx, data->tex.tex_img[E]);
	if (data->tex.tex_img[W])
		mlx_destroy_image(data->mlx, data->tex.tex_img[W]);
	ft_free_2d(data->map.map);
	ft_free_2d(data->parsing.file_content);
	free(data->parsing.line);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_printf("Error\nnote : %s\n", note);
	exit(0);
}
