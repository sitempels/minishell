/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:43:28 by user              #+#    #+#             */
/*   Updated: 2025/07/04 21:52:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_path(t_env *env, char *path)
{
	t_env	*home;

	if (path)
		return (path);
	home = env_getone(env, "HOME", 4);
	if (!home || !home->value)
	{
		printf("cd: HOME not set\n");
		return (NULL);
	}
	return (home->value);
}
int	builtin_cd(t_env *env, char *path)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd");
		oldpwd = ft_strdup("");
		if (!oldpwd)
			return (1);
	}
	path = get_target_path(env, path);
	if (!path)
	{
		free(oldpwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup(path); // on fallback sur le path donné
	if (!newpwd)
	{
		free(oldpwd);
		return (1);
	}
	env_updateone(&env, "OLDPWD", oldpwd);
	env_updateone(&env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
