/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:00:42 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 19:00:43 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "structs.h"

void	event_handler(t_game *game);
void	key_pressed(t_player *p, bool key[280]);
void	key_released(t_player *p, bool key[280]);

#endif
