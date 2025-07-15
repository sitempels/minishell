/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kerberos <kerberos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:16:30 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/05 22:11:27 by kerberos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list_node	*ft_lstlast(t_list_node *lst)
{
	t_list_node	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
