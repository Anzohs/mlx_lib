/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fload_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:19:29 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 17:19:30 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <fcntl.h>

static bool	check_borders(char **map, int w, int h)
{
	int	i;

	i = -1;
	while (++i < h)
	{
		if (map[i][0] != '1' || map[i][w] != '1')
			return (false);
	}
	i = -1;
	while (++i < w)
	{
		if (map[0][i] != '1' || map[h - 1][i] != '1')
			return (false);
	}
	return (true);
}

static void	mem_alloc(t_map *m)
{
	if (m->c > 0)
		m->c_pos = ft_calloc(m->c + 1, sizeof(t_vector));
	if (m->x > 0)
		m->x_pos = ft_calloc(m->x + 1, sizeof(t_vector));
}

static void	copy_positions(t_map *m, int w, int h, int *i)
{
	if (m->map[h][w] == 'E')
		m->e_pos = (t_vector){w, h};
	if (m->map[h][w] == 'C')
	{
		m->c_pos[*i] = (t_vector){w, h};
		(*i)++;
	}
	if (m->map[h][w] == 'X')
	{
		m->x_pos[*i] = (t_vector){w, h};
		(*i)++;
	}
}

static void	check_pos(t_map *m, int y)
{
	int	x;
	int	i;
	int	j;

	mem_alloc(m);
	if (!m->c_pos || (!m->x_pos && m->x > 0))
		free_map(m);
	i = 0;
	j = 0;
	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x && m->map[y][x])
		{
			if (m->map[y][x] == 'X')
				copy_positions(m, x, y, &j);
			else
				copy_positions(m, x, y, &i);
		}
	}
}

int	fload_fill(t_map *m)
{
	if (!check_map(m, -1) || !check_borders(m->map, m->size.x - 1, m->size.y))
		return (0);
	check_pos(m, -1);
	return (fload_helper(m));
}
