/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:40:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 21:59:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		result[i] = envp_getone(tmp);
		if (!result[i])
		{
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
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

	tmp = env_getone(env, "PATH", 4);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

int	env_updateone(t_env **head, char *key, char *value)
{
	t_env	*tmp;

	if (!head || !*head || !key || !value)
		return (1);
	tmp = env_getone(*head, key, ft_strlen(key));
	if (!tmp)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (1);
	return (0);
}
