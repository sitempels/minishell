/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:43:28 by user              #+#    #+#             */
/*   Updated: 2025/06/10 02:52:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Something like this
int	builtin_cd(t_env *env, char *path)
{
	char	*oldpwd;
	char	*newpwd;
	t_env	*var;

	if (!path)
	{
		var = env_getone(env, "HOME", 4);
		path = var->value;
	}
	oldpwd = getcwd(NULL, 0);
	chdir(path);
	newpwd = getcwd(NULL, 0);
	env_updateone(&env, "OLDPWD", oldpwd);
	env_updateone(&env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
