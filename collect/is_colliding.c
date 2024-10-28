/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_colliding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:37 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 17:44:38 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static bool	check_pos(t_area a1, t_area a2)
{
	if (a1.v1.x > a2.v2.x || a2.v1.x > a1.v2.x)
		return (false);
	if (a1.v1.y > a2.v2.y || a2.v1.y > a1.v2.y)
		return (false);
	return (true);
}

bool	is_colliding(t_colectable c, t_player p)
{
	return (check_pos((t_area){c.pos, (t_vector){c.pos.x + 16, c.pos.y + 16}}, \
		(t_area){p.pos, (t_vector){p.pos.x + 16, p.pos.y + 27}}));
}
