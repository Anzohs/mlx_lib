/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:26:10 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 00:26:12 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <stdio.h>

static void	wrong_dimentions(int fd, char *line, int n)
{
	close(fd);
	free(line);
	error_message(n);
}

static t_vector	get_dimensions(char *file)
{
	t_vector	dim;
	int			fd;
	char		*line;

	dim = (t_vector){0};
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message(3);
	line = get_next_line(fd);
	dim.x = ft_strlen(line);
	while (line)
	{
		dim.y++;
		if (dim.x != ft_strlen(line))
			wrong_dimentions(fd, line, 2);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	dim.x--;
	return (dim);
}

static char	*str_cpyn(char *src)
{
	int		i;
	int		len;
	char	*dst;

	i = -1;
	if (src[ft_strlen(src) - 1] == '\n')
		len = ft_strlen(src);
	else
		len = ft_strlen(src) + 1;
	dst = (char *)ft_calloc(len, sizeof(char *));
	if (!dst)
		return (NULL);
	while (src[++i] && i < len)
	{
		dst[i] = src[i];
	}
	return (dst);
}

static void	copy_map(t_map *m, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		m->map[i] = str_cpyn(line);
		free(line);
		if (!m->map[i++])
		{
			close(fd);
			free_map(m);
		}
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

t_map	init_map(char *file)
{
	t_map	m;
	int		index;
	int		fd;

	m = (t_map){0};
	m.size = get_dimensions(file);
	if (m.size.y < 3)
		error_message(2);
	m.map = (char **)ft_calloc(m.size.y + 1, sizeof(char *));
	fd = open(file, O_RDONLY);
	if (!m.map || fd < 0)
	{
		if (m.map)
			free(m.map);
		error_message(1);
	}
	copy_map(&m, fd);
	if (!fload_fill(&m))
		free_map(&m);
	printf("valid map");
	return (m);
}
