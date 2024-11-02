/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:31:26 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 18:31:27 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static int	num_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		++i;
	}
	return (i);
}

static char	*int_to_string(unsigned int n)
{
	int		len;
	char	*c;

	len = num_len(n);
	c = ft_calloc(len + 1, sizeof(char));
	if (!c)
		return (NULL);
	while (--len >= 0)
	{
		c[len] = (n % 10) + '0';
		n /= 10;
	}
	return (c);
}

void	mlx_put_str(t_game *g)
{
	char	*c;

	c = int_to_string(g->p.walk);
	if (c)
	{
		mlx_string_put(g->mlx, g->win.win, g->win.size.x - 50, \
			g->win.size.y - 10, 0, c);
		free(c);
	}
}
