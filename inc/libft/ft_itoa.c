/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:14:09 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:14:11 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long n)
{
	int	len_maloc;

	len_maloc = 0;
	if (n < 0)
	{
		n *= -1;
		len_maloc++;
	}
	while (n > 9)
	{
		n /= 10;
		len_maloc++;
	}
	if (n >= 0 && n < 10)
		len_maloc++;
	return (len_maloc + 1);
}

char	*ft_itoa(int n)
{
	long	l;
	char	*itoa;
	int		i;

	l = n;
	i = get_len(n);
	itoa = ft_calloc(i, sizeof(char));
	if (!itoa)
		return (NULL);
	itoa[--i] = '\0';
	l = n;
	if (n < 0)
	{
		itoa[0] = '-';
		l *= -1;
	}
	while (l > 9)
	{
		itoa[--i] = l % 10 + '0';
		l /= 10;
	}
	itoa[--i] = l + '0';
	return (itoa);
}
