/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:14:12 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 08:40:06 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_front(t_list_node **alst, t_list_node *new_node)
{
	if (!new_node)
		return ;
	new_node->next = *alst;
	*alst = new_node;
}
