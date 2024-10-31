/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:49:36 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/31 19:49:37 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	reset_flags(t_player *p, int row)
{
	p->anim.row = row;
	p->anim.animating = true;
}

static void	attack(t_player *p)
{
	p->anim.sword_anim = true;
	p->anim.animating = false;
	p->anim.frame = 0;
}

static void	is_anim(t_player *p)
{
	if (!p->anim.down && !p->anim.up && \
		!p->anim.left && !p->anim.right)
	{
		p->anim.animating = false;
		p->anim.frame = 0;
	}
}

void	key_pressed(t_player *p, bool key[280])
{
	if ((key[32] || key[49]))
		attack(p);
	else if (key[13] || key[119])
	{
		p->anim.up = 1;
		reset_flags(p, 2);
	}
	else if (key[115] || key[1])
	{
		p->anim.down = 1;
		reset_flags(p, 0);
	}
	else if (key[97] || key[0])
	{
		p->anim.left = 1;
		reset_flags(p, 3);
	}
	else if (key[100] || key[2])
	{
		p->anim.right = 1;
		reset_flags(p, 1);
	}
	else
		is_anim(p);
}
