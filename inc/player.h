/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:41:04 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 18:41:05 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

void	wall_collide(t_player *p, t_map *map, double dt);
void	player_to_world(t_img *w, t_img *p, t_vector pos);
void	player_start(t_game *g);
void	draw_p(t_game *g, int src_x, int src_y);
void	player_update(t_game *g, t_player *p, double dt);
void	is_player_dead(t_game *g);
#endif
