/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:18:52 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/10 21:29:01 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list_node	*ft_lstmap(t_list_node *lst, void *(*f)(void *))
{
	t_list_node	*new_list;
	t_list_node	*new_obj;
	void		*obj;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		obj = f(lst->data);
		new_obj = ft_lstnew(obj);
		if (!new_obj)
		{
			free(obj);
			ft_lstclear(&new_list, free);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_obj);
		lst = lst->next;
	}
	return (new_list);
}
