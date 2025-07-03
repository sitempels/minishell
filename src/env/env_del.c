/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:52:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:11:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_delone(t_env **head, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!head || !*head || !key)
		return (1);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			env_freeone(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}
