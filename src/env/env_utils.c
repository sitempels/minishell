/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:40:00 by user              #+#    #+#             */
/*   Updated: 2025/07/10 18:14:24 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*envp_getone(t_env *env)
// {
// 	char	*result;
// 	char	*tmp;

// 	if (!env || !env->key || !env->value)
// 		return (NULL);
// 	result = ft_strjoin(env->key, "=");
// 	if (!result)
// 		return (NULL);
// 	tmp = ft_strjoin(result, env->value);
// 	free(result);
// 	return (tmp);
// }

// char	**envp_from_env(t_env *env)
// {
// 	char	**result;
// 	t_env	*tmp;
// 	size_t	i;

// 	if (!env)
// 		return (NULL);
// 	result = ft_calloc(env_size(env) + 1, sizeof(char *));
// 	if (!result)
// 		return (NULL);
// 	tmp = env;
// 	i = 0;
// 	while (tmp)
// 	{
// 		result[i] = envp_getone(tmp);
// 		if (!result[i])
// 		{
// 			while (i--)
// 				free(result[i]);
// 			free(result);
// 			return (NULL);
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (result);
// }

char	*envp_getone(t_env *env)
{
	char	*result;
	char	*tmp;

	if (!env || !env->key || !env->value)
		return (NULL);
	result = ft_strjoin(env->key, "=");
	if (!result)
		return (NULL);
	tmp = ft_strjoin(result, env->value);
	free(result);
	return (tmp);
}

char	**envp_from_env(t_env *env)
{
	char	**result;
	t_env	*tmp;
	size_t	i;

	if (!env)
		return (NULL);
	result = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			result[i] = envp_getone(tmp);
			if (!result[i])
			{
				while (i--)
					free(result[i]);
				return (free(result), NULL);
			}
			i++;
		}
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}

char	**env_getallpaths(char *path)
{
	char	**paths;

	if (!path)
		return (NULL);
	paths = ft_strsplit(path, ':');
	return (paths);
}

char	*env_getpath(t_env *env)
{
	t_env	*tmp;

	tmp = env_getone(env, "PATH");
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

int	env_updateone(t_env **head, char *key, char *value)
{
	t_env	*node;
	t_env	*new;
	char	*entry;

	if (!head || !key)
		return (1);
	node = env_getone(*head, key);
	if (!node)
	{
		if (value)
		{
			entry = ft_strjoin_var(3, key, "=", value);
			if (!entry)
				return (1);
		}
		else
		{
			entry = ft_strdup(key);
			if (!entry)
				return (1);
		}
		new = new_env(entry);
		free(entry);
		if (!new || env_addback(head, new))
			return (env_freeone(new), 1);
		return (0);
	}
	if (value)
	{
		free(node->value);
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
	}
	return (0);
}
