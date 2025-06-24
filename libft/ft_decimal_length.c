/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:11:06 by jaoh              #+#    #+#             */
/*   Updated: 2024/08/01 18:11:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_decimal_length(long int nbr)
{
	int	length;

	length = 0;
	if (nbr <= 0)
		length++;
	while (nbr)
	{
		nbr /= 10;
		length++;
	}
	return (length);
}
