/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:54:30 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/22 22:54:45 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	error_message(int error)
{
	if (error == 1)
		ft_putstr_fd("Error Wrong number of arguments\n", 2);
	if (error == 2)
		ft_putstr_fd("Error Invalid map\n", 2);
	if (error == 3)
		ft_putstr_fd("Error Reading the file\n", 2);
	exit(0);
}
