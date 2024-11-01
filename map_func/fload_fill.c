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

static bool	is_valid(char c)
{
	return (c == '0' || c == '1' || c == 'C' \
		|| c == 'P' || c == 'E' || c == 'X');
}

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

static void	check_pos(t_map *m, int y)
{
	int	x;
	int	i;

	ft_putnbr_fd(m->x, 2);
	m->c_pos = (t_vector *)ft_calloc(m->c + 1, sizeof(t_vector));
	m->x_pos = (t_vector *)ft_calloc(m->x + 1, sizeof(t_vector));
	if (!m->c_pos)
		free_map(m);
	i = 0;
	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x && m->map[y][x])
		{
			if (m->map[y][x] == 'E')
			{
				m->e_pos.x = x;
				m->e_pos.y = y;
			}
			if (m->map[y][x] == 'C')
			{
				m->c_pos[i].x = x;
				m->c_pos[i].y = y;
				i++;
			}
			if (m->map[y][x] == 'X')
			{
				m->x_pos[i].x = x;
				m->x_pos[i].y = y;
				i++;
			}
		}
	}
}

static int	check_map(t_map *m, int y)
{
	int	x;

	while (++y < m->size.y)
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
			if (m->map[y][x] == 'X')
				m->x++;
		}
	}
	if (m->e != 1 || m->p != 1 || m->c < 1)
		return (0);
	return (1);
}

int	fload_fill(t_map *m)
{
	if (!check_map(m, -1) || !check_borders(m->map, m->size.x - 1, m->size.y))
		return (0);
	check_pos(m, -1);
	return (fload_helper(m));
}
