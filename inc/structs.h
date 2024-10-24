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

# include <stdbool.h>

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

typedef struct s_map
{
	char		**map;
	t_vector	size;
	t_vector	p_pos;
	t_vector	e_pos;
	t_vector	x_pos;
	t_vector	*c_pos;
	int			c;
	int			p;
	int			e;
	int			x;
}				t_map;

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
	t_vector		pos;
	t_img			sprite;
	int				health;
	int				score;
	unsigned int	walk;
}	t_player;

typedef struct s_colectable
{
	t_vector	pos;
	t_img		img;
	bool		collected;
}	t_colectable;

typedef struct s_enemy
{
	t_vector	pos;
	t_img		sprite;
}	t_enemy;

typedef struct s_exit
{
	t_vector	pos;
	t_img		sprite;
	bool		is_open;
}		t_exit;

typedef struct s_b
{
	t_img	wall;
	t_img	floor;
}		t_b;

typedef struct s_game
{
	void			*mlx;
	t_win			win;
	t_img			state;
	t_b				i_map;
	t_img			cam;
	t_img			world;
	t_vector		size;
	t_player		p;
	t_colectable	*c;
	t_exit			e;
	void			(*loop)(struct s_game *g);
}		t_game;

#endif
