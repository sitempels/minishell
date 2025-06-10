/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:00:47 by user              #+#    #+#             */
/*   Updated: 2025/06/10 04:11:20 by user             ###   ########.fr       */
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
	return (shell);
}
