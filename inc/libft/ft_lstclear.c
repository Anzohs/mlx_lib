/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:14:47 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:14:48 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list_t;
	t_list	*list_temp;

	list_t = *lst;
	if (!*lst || !del)
		return ;
	while (list_t)
	{
		del(list_t->content);
		list_temp = list_t->next;
		free(list_t);
		list_t = list_temp;
	}
	*lst = NULL;
}
