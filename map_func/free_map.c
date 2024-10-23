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

void	free_map(t_map *m)
{
	int	i;

	i = -1;
	while (m->map[++i])
		free(m->map[i]);
	free(m->map);
	error_message(3);
}
