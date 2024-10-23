/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:29:27 by hladeiro          #+#    #+#             */
/*   Updated: 2024/05/13 21:13:23 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1];
	t_data		data;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	data.n = 0;
	data.i = 1;
	data.line = NULL;
	while (!data.n)
	{
		if (!*str)
		{
			data.i = read(fd, str, BUFFER_SIZE);
			if (data.i > BUFFER_SIZE)
			{
				ft_error_handler(str, &data);
				return (NULL);
			}
			if (data.i == 0)
				return (data.line);
			str[data.i] = 0;
		}
		ft_get_line(str, &data);
	}
	return (data.line);
}
