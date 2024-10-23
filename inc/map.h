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

int		fload_helper(t_map *m);
t_map	init_map(char *file);
int		fload_fill(t_map *m);
void	error_message(int e);
void	free_map(t_map *m);
int		valid_name(char *s, int l);

#endif
