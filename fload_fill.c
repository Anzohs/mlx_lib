/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fload_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:00:42 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/22 19:00:43 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "map.h"

static bool	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'C' \
		|| c == 'P' || c == 'E' || c == 'X' );
}

static bool	check_borders(char **map, int w, int h)
{
	int	i;

	i = -1;
	while (++i < h)
	{
		if (map[i][0] != '1' || map[i][w] != '1' )
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

static void	flood_fill(char **map, int w, int h, bool **visited, t_map *m)
{
	if (w < 0 || h < 0 || !map[h] || !map[h][w] || \
		visited[h][w] || map[h][w] == '1' || w >= m->size.x || h >= m->size.y)
		return ;
	visited[h][w] = true;
	flood_fill(map, w + 1, h, visited, m);
	flood_fill(map, w - 1, h, visited, m);
	flood_fill(map, w, h + 1, visited, m);
	flood_fill(map, w, h - 1, visited, m);
}

int	fload_fill(t_map *m)
{
	int		x;
	int		y;
	bool	**visited;
	bool	v;

	if (!check_borders(m->map, m->size.x - 1, m->size.y))
		return (0);
	y = -1;
	while(++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x && m->map[y][x])
		{
			if (!is_valid(m->map[y][x]))
				return (0);
			if (m->map[y][x] == 'P')
			{
				m->p_pos.x = x;
				m->p_pos.y = y;
				m->p++;
			}
			if (m->map[y][x] == 'E')
				m->e++;
			if (m->map[y][x] == 'C')
				m->c++;
		}
	}
	if (m->e != 1 || m->p != 1 || m->c < 1)
		return (0);
	visited = (bool **)ft_calloc(m->size.y, sizeof(bool *));
	if (!visited)
		return (0);
	y = -1;
	v = true;
	while (++y < m->size.y)
		visited[y] = (bool *)ft_calloc(m->size.x, sizeof(bool));
	y = -1;
	flood_fill(m->map, m->p_pos.x, m->p_pos.y, visited, m);
	while (++y < m->size.y && v)
	{
		x = -1;
		while (++x < m->size.x)
		{
			if ((m->map[y][x] == 'C' || m->map[y][x] == 'E') && !visited[y][x])
			{
				v = false;
				break;
			}
		}
	}

	y = -1;
	while(++y < m->size.y)
		free(visited[y]);
	free(visited);
	return (v);
}
