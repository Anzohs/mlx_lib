/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:41 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:42 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	char	l;
	int		i;

	i = (int)ft_strlen(s);
	l = (char) c;
	while (i > 0)
	{
		if (s[i] == l)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == l)
		return ((char *)s + i);
	return (NULL);
}
