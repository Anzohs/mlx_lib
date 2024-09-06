/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:32:03 by hladeiro          #+#    #+#             */
/*   Updated: 2024/09/06 00:15:47 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "structs.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

t_vector	*ft_init_vector(int x, int y);
t_fvector	*ft_init_fvector(float x, float y);
t_data		*ft_init_data(void);
t_game		*ft_init_game(void);
t_map		*ft_init_map(void);
void		ft_start_game(t_game *game);
void		ft_render(t_game *game);
void		free_data(t_game *game);
int			ft_update(t_game *game);
int			ft_key_press(int keycode, t_game *game);

#endif
