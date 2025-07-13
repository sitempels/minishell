/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/07/13 10:25:50 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
void	builtin_exit(t_shell *shell, int print, char *status)
{
	int	intstatus;

	if (print)
		ft_printf("minishell: exiting the shell...\n");
	if (status)
	{
		intstatus = ft_atoi(status);
		//add_verif to atoi for intmax\min
		shell->status = intstatus;
	}
	destroy_shell(shell);
	exit(intstatus);
}
