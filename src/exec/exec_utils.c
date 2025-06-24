/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:10:57 by stempels          #+#    #+#             */
/*   Updated: 2025/06/24 17:48:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_node(t_shell *shell, t_node *tree, t_env *env)
{
	int	status;

	if (!tree)
		return (1);
	status = tree->use.fct(shell, tree, env);
	return (status);
}

int	create_fork(t_shell *shell, pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		ft_error(shell, 0, 2, "EXEC: FORK", get_errnum(N_CREAT));
	if (*pid == 0)
		return (1);
	return (0);
}

int	create_pipe(int *nbr, t_shell *shell, int *pipefd, pid_t *pid)
{
	if (create_fork(shell, pid))
	{
		if (*nbr == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			return (1);
		}
		else if (*nbr == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			return (1);
		}
	}
	else
		(*nbr)++;
	return (0);
}
