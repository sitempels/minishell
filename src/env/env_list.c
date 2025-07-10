/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:08:28 by user              #+#    #+#             */
/*   Updated: 2025/07/10 11:10:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_getlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	env_addfront(t_env **head, t_env *new)
{
	if (!head || !new)
		return (1);
	new->next = *head;
	*head = new;
	return (0);
}

int	env_addback(t_env **head, t_env *new)
{
	t_env	*last;

	if (!head || !new)
		return (1);
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (0);
	}
	last = *head;
	while (last->next)
	{
		if (last->next == new)
			return (1);
		last = last->next;
	}
	last->next = new;
	return (0);
}

t_env	*env_getone(t_env *head, char *key, size_t len)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	env_size(t_env *env)
{
	size_t	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
