/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:43:28 by user              #+#    #+#             */
/*   Updated: 2025/07/10 18:14:09 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_invalid_option(int *exit_status)
{
	ft_putstr_fd("cd: invalid option\n", 2);
	*exit_status = 2;
	return (NULL);
}

static char	*handle_dash(t_env *env, int *exit_status)
{
	t_env	*oldpwd;

	oldpwd = env_getone(env, "OLDPWD");
	if (!oldpwd || !oldpwd->value)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		*exit_status = 2;
		return (NULL);
	}
	return (oldpwd->value);
}

static char	*handle_empty(t_env *env, int *exit_status)
{
	t_env	*home;

	home = env_getone(env, "HOME");
	if (!home || !home->value)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		*exit_status = 2;
		return (NULL);
	}
	return (home->value);
}

static char	*get_target_path(t_env *env, char *path, int *exit_status)
{
	if (path && path[0] == '-' && path[1] && ft_strcmp(path, "-") != 0)
		return (handle_invalid_option(exit_status));
	if (path && ft_strcmp(path, "-") == 0)
		return (handle_dash(env, exit_status));
	if (path)
		return (path);
	return (handle_empty(env, exit_status));
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
	{
		newpwd = ft_strdup("");
		if (!newpwd)
		{
			free(oldpwd);
			return (1);
		}
	}
	if (env_updateone(&env, "OLDPWD", oldpwd))
	{
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	if (env_updateone(&env, "PWD", newpwd))
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
	char	*target;
	int		exit_status;

	exit_status = 0;
	oldpwd = get_safe_cwd();
	if (!oldpwd)
		return (1);
	target = get_target_path(env, path, &exit_status);
	if (!target)
	{
		free(oldpwd);
		return (exit_status);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		// return (1);
		return (errno);
	}
	newpwd = getcwd(NULL, 0);
	return (update_env_dirs(env, oldpwd, newpwd));
}
