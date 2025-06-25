/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/06/25 10:02:50 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
int	builtin_exit(t_shell *shell, char *argv)
{
	int	status;
	if (!argv)
		status = 0;
	else
		status = ft_atoi(argv);
	printf("exit\n");
	(void)shell;
	destroy_shell(shell);
	exit(status);
}
