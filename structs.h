/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    :+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:18:51 by hladeiro          #+#    #+#             */
/*   Updated: 2024/09/06 00:08:48 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "42_libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_fvector
{
	float	x;
	float	y;
}				t_fvector;

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_map
{
	t_vector	*pos;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
}				t_data;

typedef struct s_game
{
	t_data	*data;
	t_map	*map;
	void	(*init)(struct s_game *game);
	void	(*render)(struct s_game *game);
	int		(*update)(struct s_game *game);
}				t_game;

#endif
