/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:38:35 by jaoh              #+#    #+#             */
/*   Updated: 2025/06/25 14:38:40 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ps_is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	ps_is_cub(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	ps_is_xpm(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	ps_check_file(char *arg, bool cub)
{
	int	fd;

	if (ps_is_dir(arg))
		return (err_msg(arg, "Is a directory", FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	if (cub && !ps_is_cub(arg))
		return (err_msg(arg, "Not a .cub file", FAILURE));
	if (!cub && !ps_is_xpm(arg))
		return (err_msg(arg, "Not an .xpm file", FAILURE));
	return (SUCCESS);
}
