/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:20:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:09:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *env)
{
	size_t	len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, len + 1);
	return (key);
}

char	*extract_value(char *env)
{
	size_t	start;
	char	*value;

	start = 0;
	while (env[start] && env[start] != '=')
		start++;
	if (!env[start])
		return (NULL);
	start++;
	value = ft_strdup(&env[start]);
	return (value);
}

t_env	*new_env(char *env)
{
	t_env	*new;
	char	*key;
	char	*value;

	if (!ft_strchr(env, '='))
		return (NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	key = extract_key(env);
	value = extract_value(env);
	if (!key || !value)
		return (free(key), free(value), free(new), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_freeone(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
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
