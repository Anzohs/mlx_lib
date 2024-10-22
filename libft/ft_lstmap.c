/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:15:28 by hladeiro          #+#    #+#             */
/*   Updated: 2024/04/18 19:15:29 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lst_new(void *content)
{
	t_list	*n_list;

	if (!content)
		return (NULL);
	n_list = (t_list *)malloc(sizeof(*n_list));
	if (!n_list)
		return (NULL);
	n_list->content = content;
	n_list->next = NULL;
	return (n_list);
}

static t_list	*ft_lst_last(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	lstadd_last(t_list **lst, t_list *new)
{
	t_list	*new_list;

	new_list = ft_lst_last(*lst);
	if (!new_list)
		*lst = new;
	else
		new_list->next = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*list_t;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	if (!new_list)
	{
		new_list = lst_new(f(lst->content));
		if (!new_list->content)
			del(new_list->content);
		lst = lst->next;
	}
	while (lst)
	{
		list_t = lst_new(f(lst->content));
		lstadd_last(&new_list, list_t);
		lst = lst->next;
	}
	return (new_list);
}
