/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:23:09 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/24 20:23:10 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../inc/structs.h"
# include "../mlx/mlx.h"

void	init_world(t_game *g, t_vector size);
void	write_world(t_game *g, t_map m);

#endif
