/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:43:28 by user              #+#    #+#             */
/*   Updated: 2025/07/15 18:13:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_dirs(t_env *env, char *oldpwd, char *newpwd)
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
		return (free(oldpwd), exit_status);
	if (chdir(target) != 0)
		return (perror("cd"), free(oldpwd), errno);
	newpwd = get_safe_cwd();
	if (!newpwd)
		return (free(oldpwd), 1);
	return (update_env_dirs(env, oldpwd, newpwd));
}
