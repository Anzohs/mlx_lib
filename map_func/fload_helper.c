/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fload_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:22:20 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 18:22:22 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include <stdbool.h>

static void	flood_fill(t_map *m, int w, int h, bool **visited)
{
	if (w < 0 || h < 0 || !m->map[h][w] || visited[h][w] || \
		m->map[h][w] == '1' || w >= m->size.x || h >= m->size.y)
		return ;
	visited[h][w] = true;
	flood_fill(m, w + 1, h, visited);
	flood_fill(m, w - 1, h, visited);
	flood_fill(m, w, h + 1, visited);
	flood_fill(m, w, h - 1, visited);
}

static void	free_visited(bool **v, int size)
{
	int	y;

	y = -1;
	while (++y < size)
		free(v[y]);
	free(v);
}

static int	aloc_bool(bool **v, int y, int x)
{
	int	i;

	i = -1;
	while (++i < y)
	{
		v[i] = (bool *)ft_calloc(x, sizeof(bool));
		if (!v[i])
		{
			free_visited(v, y);
			return (0);
		}
	}
	return (1);
}

static bool	check_visited(bool **v, t_vector size, char **map)
{
	int		x;
	int		y;
	bool	b;

	b = true;
	y = -1;
	while (++y < size.y && b)
	{
		x = -1;
		while (++x < size.x)
		{
			if ((map[y][x] == 'C' || map[y][x] == 'E') && !v[y][x])
			{
				b = false;
				break ;
			}
		}
	}
	return (b);
}

int	fload_helper(t_map *m)
{
	bool	**visited;
	bool	v;

	visited = (bool **)ft_calloc(m->size.y, sizeof(bool *));
	if (!visited)
		return (0);
	if (!aloc_bool(visited, m->size.y, m->size.x))
		return (0);
	flood_fill(m, m->p_pos.x, m->p_pos.y, visited);
	v = check_visited(visited, m->size, m->map);
	free_visited(visited, m->size.y);
	return (v);
}
