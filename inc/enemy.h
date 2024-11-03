/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:08:19 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 19:08:20 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# include "structs.h"

void	init_enemy(t_game *g, int n);
void	draw_enemy(t_game *g);
void	update_enemy(t_game *g, double dt);
void	enemy_move(t_enemy *e, t_map *m, double dt);
void	animation_up(t_enemy *e, double dt);

#endif
