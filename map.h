/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:33 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/22 18:41:35 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "structs.h"
# include <stddef.h>

typedef struct s_map
{
	char		**map;
	t_vector	size;
	t_vector	p_pos;
	int			c;
	int			p;
	int			e;
	int			x;
}				t_map;

int	fload_fill(t_map *m);
#endif
