/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 07:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/15 07:30:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_invalid_option(int *exit_status)
{
	ft_putstr_fd("cd: invalid option\n", 2);
	*exit_status = 2;
	return (NULL);
}

char	*handle_dash(t_env *env, int *exit_status)
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

char	*handle_empty(t_env *env, int *exit_status)
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

char	*get_target_path(t_env *env, char *path, int *exit_status)
{
	if (path && path[0] == '-' && path[1] && ft_strcmp(path, "-") != 0)
		return (handle_invalid_option(exit_status));
	if (path && ft_strcmp(path, "-") == 0)
		return (handle_dash(env, exit_status));
	if (path)
		return (path);
	return (handle_empty(env, exit_status));
}

char	*get_safe_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("cd");
	return (cwd);
}
