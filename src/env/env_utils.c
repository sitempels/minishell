/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 07:13:52 by user              #+#    #+#             */
/*   Updated: 2025/07/15 07:14:54 by user             ###   ########.fr       */
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

static void	free_envp_array(char **envp, size_t count)
{
	while (count--)
		free(envp[count]);
	free(envp);
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
	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			result[i] = envp_getone(tmp);
			if (!result[i])
				return (free_envp_array(result, i), NULL);
			i++;
		}
		tmp = tmp->next;
	}
	return (result);
}

char	**env_getallpaths(char *path)
{
	if (!path)
		return (NULL);
	return (ft_strsplit(path, ':'));
}

char	*env_getpath(t_env *env)
{
	t_env	*tmp;

	tmp = env_getone(env, "PATH");
	if (!tmp)
		return (NULL);
	return (tmp->value);
}
