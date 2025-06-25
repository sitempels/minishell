/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/06/25 13:58:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
int	builtin_exit(t_shell *shell, int print, int status)
{
	if (print)
		ft_printf("exit\n");
	shell->status = status;
	(void)shell;
	destroy_shell(shell);
	exit(status);
}
