/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:48:01 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/22 17:48:02 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"

void	error_mensage(int error)
{
	if (error == 1)
		ft_putstr_fd("Wrong number of arguments\n", 2);
	if (error == 2)
		ft_putstr_fd("Invalid map\n", 2);
	if (error == 3)
		ft_putstr_fd("Error reading the file\n", 2);
	exit(0);
}

static t_vector	success(char *map_name)
{
	char		*map;
	t_vector	len;
	int			fd;

	len = (t_vector){0};
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		error_mensage(3);
	map = get_next_line(fd);
	len.x = ft_strlen(map);
	while (map)
	{
		len.y++;
		if (len.x != ft_strlen(map))
		{
			if (map[len.x - 1] != '0')
			{
				close(fd);
				free(map);
				error_mensage(2);
			}
		}
		free(map);
		map = get_next_line(fd);
	}
	free(map);
	close(fd);
	return (len);
}

static int	valid_name(char *c, int len)
{
	len--;
	if (c[len] != 'r' || c[len -1] != 'e')
		return (0);
	len -= 2;
	if (c[len] != 'b' || c[len - 1] != '.')
		return (0);
	return (1);
}

static void	start_(char *map)
{
	t_map	m;
	int		fd;
	int		index;

	index = -1;
	m = (t_map){0};
	m.size = success(map);
	if (m.size.y < 3)
		error_mensage(2);
	m.map = (char **)ft_calloc(m.size.y + 1, sizeof(char *));
	fd = open(map, O_RDONLY);
	if (fd < 0 || !m.map)
	{
		if (m.map)
			free(m.map);
		error_mensage(3);
	}
	while (++index < m.size.y)
		m.map[index] = get_next_line(fd);
	close(fd);
	if (!fload_fill(&m))
	{
		while (--index > -1)
			free(m.map[index]);
		free(m.map);
		error_mensage(2);
	}
}

int	main(int ac, char **av)
{
	int	len;

	if (ac == 2)
	{
		len = ft_strlen(av[1]);
		if (len > 3 && valid_name(av[1], len))
			start_(av[1]);
		else
			error_mensage(2);
	}
	else
		error_mensage(1);
	return (0);
}
