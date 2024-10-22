/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:14:29 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/21 16:15:24 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vector
{
	int		x;
	int		y;
}		t_vector;

typedef struct s_area
{
	t_vector	v1;
	t_vector	v2;
}		t_area;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_vector	pos;
}		t_img;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	t_vector	size;
}		t_win;

typedef struct s_player
{
	t_vector	pos;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	t_win		win;
	t_img		state;
	t_img		cam;
	char		**map;
	t_vector	size;
	t_player	p;
	void		(*loop)(struct s_game *g);
}		t_game;

#endif
