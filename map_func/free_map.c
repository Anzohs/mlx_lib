/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:06:00 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 17:06:01 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	free_enm(t_map *m)
{
	if (!m->x_pos || m->x < 1)
		return ;
	free(m->x_pos);
}

static void	free_col(t_map *m)
{
	if (!m->c_pos || m->c < 1)
		return ;
	free(m->c_pos);
}

void	free_map(t_map *m)
{
	int	i;

	i = -1;
	while (m->map[++i])
		free(m->map[i]);
	free_col(m);
	free_enm(m);
	free(m->map);
	error_message(3);
}
