/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:43:28 by user              #+#    #+#             */
/*   Updated: 2025/07/09 16:10:41 by sjacquet         ###   ########.fr       */
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
		printf("cd: home not set in env\n");
		return (NULL);
	}
	return (home->value);
}

static char	*get_safe_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("cd");
	return (cwd);
}

static int	update_env_dirs(t_env *env, char *oldpwd, char *newpwd)
{
	if (!newpwd)
		newpwd = ft_strdup("");
	if (!newpwd)
		return (free(oldpwd), 1);
	if (env_updateone(&env, "OLDPWD", oldpwd) || env_updateone(&env, "PWD",
			newpwd))
	{
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	builtin_cd(t_env *env, char *path)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_safe_cwd();
	if (!oldpwd)
		return (1);
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
	return (update_env_dirs(env, oldpwd, newpwd));
}
