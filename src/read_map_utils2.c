/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:16:10 by chanypar          #+#    #+#             */
/*   Updated: 2025/05/09 11:11:32 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (c == '\n')
	{
		if (!s[0])
			return (0);
		while (s[++i])
		{
			if (s[i] == '\n')
				count++;
		}
		return (count + 1);
	}
	else
	{
		while (s[++i])
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
				count++;
		}
		return (count);
	}
}

static void	move_s(char *new_s, char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
}

int	split_helper(int *i, int *j, char **arr, char const *s)
{
	if (s[*j] == '\n')
	{
		arr[*i] = malloc(1);
		if (!arr[*i])
			return (1);
		arr[*i][0] = '\0';
		(*i)++;
		(*j)++;
		return (0);
	}
	return (1);
}

void	split2(char **arr, char const *s)
{
	int	i;
	int	j;
	int	token_len;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (split_helper(&i, &j, arr, s))
		{
			token_len = 0;
			while (s[j + token_len] && s[j + token_len] != '\n')
				token_len++;
			arr[i] = malloc(sizeof(char) * (token_len + 1));
			if (!arr[i])
				return ;
			move_s(arr[i], s + j, '\n');
			i++;
			j += token_len;
			if (s[j] == '\n')
				j++;
		}
	}
	arr[i] = NULL;
}

char	**ft_split_parsing(char const *s)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (count_words(s, '\n') + 1));
	if (!arr)
		return (NULL);
	split2(arr, s);
	return (arr);
}
