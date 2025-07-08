/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:50:00 by user              #+#    #+#             */
/*   Updated: 2025/07/07 17:01:33 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_size(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

t_env	*env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		node = new_env(envp[i]);
		if (!node)
		{
			env_freeall(head);
			return (NULL);
		}
		if (env_addback(&head, node) != 0)
		{
			env_freeone(node);
			env_freeall(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

void	env_freeall(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		env_freeone(env);
		env = tmp;
	}
}
