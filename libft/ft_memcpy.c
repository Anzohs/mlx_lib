/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:16:27 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:16:28 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*pt;

	if (!src && !dest)
		return (dest);
	ptr = (unsigned char *) dest;
	pt = (unsigned char *) src;
	while (n)
	{
		*ptr = *pt;
		ptr++;
		pt++;
		n--;
	}
	return (dest);
}
