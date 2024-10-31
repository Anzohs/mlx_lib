/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_released.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:55:51 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/31 19:55:51 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	key_released(t_player *p, bool key[280])
{
	if (!key[13] || !key[119])
		p->anim.up = 0;
	if (!key[115] || !key[1])
		p->anim.down = 0;
	if (!key[97] || !key[0])
		p->anim.left = 0;
	if (!key[100] || !key[2])
		p->anim.right = 0;
	if ((!key[32] || !key[49]) && p->anim.sword_anim)
		p->anim.animating = true;
}
