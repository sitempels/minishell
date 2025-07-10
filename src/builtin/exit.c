/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/07/10 17:00:19 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
void	builtin_exit(t_shell *shell, int print, int status)
{
	if (print)
		ft_printf("minishell: exiting the shell...\n");
	shell->status = status;
	destroy_shell(shell);
	exit(status);
}
