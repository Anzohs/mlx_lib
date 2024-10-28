/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:05:01 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 19:05:03 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	start_collect(t_game *g, int n)
{
	int	i;

	i = -1;
	g->c.c = (t_colectable *)ft_calloc(n + 1, sizeof(t_colectable));
	collect_img(g, &g->c);
	collected_img(g, &g->c);
	while (++i < n)
		g->c.c[i] = (t_colectable){0};
	save_collect(g, g->map);
}
