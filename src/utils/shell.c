/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:00:47 by user              #+#    #+#             */
/*   Updated: 2025/06/25 09:28:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(int mode, char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cli = NULL;
	shell->env = env_from_envp(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->mode = mode;
	shell->status = 0;
	shell->std_io[0] = ttyname(STDOUT_FILENO);
	shell->std_io[1] = ttyname(STDIN_FILENO);
	if (update_envint(shell->env, "SHLVL", 0, 1))
		ft_error(shell, 0, 1, "LOST IS SHELL LVL");
	return (shell);
}

int	update_envint(t_env *env, char *key, size_t len, int modif)
{
	t_env	*target;

	if (len == 0)
		len = ft_strlen(key);
	target = env_getone(env, key, len);
	if (!target)
		return (1);
	target->value = ft_itoa(ft_atoi(target->value) + modif);
	return (0);
}
