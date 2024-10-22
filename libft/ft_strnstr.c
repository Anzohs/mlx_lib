/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:35 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:18:36 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_c(const char *big, const char *little, size_t len, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (big[i] && i < (int)len && little[j])
	{
		if (big[i] == little[j])
		{
			k++;
			j++;
		}
		else
		{
			j = 0;
			i -= k;
			k = 0;
		}
		i++;
	}
	if (!little[j])
		return ((char *) big + (i - k));
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;

	i = 0;
	if (!little)
		return ((char *) big);
	return (find_c(big, little, len, i));
}
