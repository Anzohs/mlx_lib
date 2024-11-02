/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:22:03 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 17:22:04 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

int	check_map(t_map *m, int y)
{
	int	x;

	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x)
		{
			if (!is_valid_map(m->map[y][x]))
				return (0);
			if (m->map[y][x] == 'P')
			{
				m->p_pos = (t_vector){x, y};
				m->p++;
			}
			else if (m->map[y][x] == 'E')
				m->e++;
			else if (m->map[y][x] == 'C')
				m->c++;
			else if (m->map[y][x] == 'X')
				m->x++;
		}
	}
	if (m->e != 1 || m->p != 1 || m->c < 1)
		return (0);
	return (1);
}
