/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/07/31 07:17:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
// add_verif to atoi for intmax\min
void	builtin_exit(t_shell *shell, int print, char **status)
{
	int	intstatus;

	if (print == 0)
		write(2, "exit\n", 5);
	if (status && status[1])
	{
		intstatus = ft_atoi(status[1]);
		shell->status = intstatus;
	}
	else
		intstatus = shell->status;
	if (status)
		ft_free_array_pos(&status, 0);
	destroy_shell(shell);
	exit(intstatus);
}
