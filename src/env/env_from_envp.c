/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:50:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:10:47 by user             ###   ########.fr       */
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
	t_env	*env;
	size_t	i;

	head = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env = new_env(envp[i]);
		if (!env)
		{
			env_freeall(head);
			return (NULL);
		}
		if (env_addback(&head, env) != 0)
		{
			env_freeall(head);
			env_freeone(env);
			return (NULL);
		}
		i++;
	}
	return (head);
}
