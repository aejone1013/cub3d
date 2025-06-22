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

#include "cub3d.h"

void	ft_free_2d(char **str) // 2차원 배열 메모리 해제
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

int	check_argv(char *argv) // 확장자가 ".cub" 인지 확인
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

void	error(char *note, int error_code, t_data *data) // 에러 확인 후, 메모리 해제
{
	if (error_code == 2 && data->window)
        mlx_destroy_window(data->mlx, data->window);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
    free_data(data);
    ft_printf("Error\nnote : %s\n", note);
    exit(1);
}
