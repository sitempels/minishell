/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 07:13:52 by user              #+#    #+#             */
/*   Updated: 2025/07/15 07:15:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_add_or_update(t_env **head, char *key, char *value)
{
	t_env	*new;
	char	*entry;

	if (value)
		entry = ft_strjoin_var(3, key, "=", value);
	else
		entry = ft_strdup(key);
	if (!entry)
		return (1);
	new = new_env(entry);
	free(entry);
	if (!new || env_addback(head, new))
		return (env_freeone(new), 1);
	return (0);
}

int	env_updateone(t_env **head, char *key, char *value)
{
	t_env	*node;

	if (!head || !key)
		return (1);
	node = env_getone(*head, key);
	if (!node)
		return (env_add_or_update(head, key, value));
	if (value)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
	}
	return (0);
}
