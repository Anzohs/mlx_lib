/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:17:33 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:17:34 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			l;

	i = 0;
	l = (char) c;
	while (s[i])
	{
		if (s[i] == l)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == l)
		return ((char *) s + i);
	return (NULL);
}
