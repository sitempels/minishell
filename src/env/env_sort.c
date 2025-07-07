/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:54:00 by user              #+#    #+#             */
/*   Updated: 2025/07/07 16:21:56 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_swap_content(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

t_env	*env_dup(t_env *src)
{
	t_env	*copy;
	t_env	*new;

	copy = NULL;
	while (src)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
		{
			env_freeall(copy);
			return (NULL);
		}
		new->key = ft_strdup(src->key);
		if (src->value)
			new->value = ft_strdup(src->value);
		else
			new->value = NULL;
		if (!new->key || (src->value && !new->value))
		{
			env_freeall(copy);
			env_freeone(new);
			return (NULL);
		}
		env_addback(&copy, new);
		src = src->next;
	}
	return (copy);
}

int	env_sortkey(t_env **head)
{
	t_env	*i;
	t_env	*j;
	t_env	*copy;

	if (!head || !*head)
		return (1);
	copy = env_dup(*head);
	if (!copy)
		return (1);
	i = copy;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				env_swap_content(i, j);
			j = j->next;
		}
		i = i->next;
	}
	env_freeall(*head);
	*head = copy;
	return (0);
}
