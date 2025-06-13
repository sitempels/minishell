/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:56 by user              #+#    #+#             */
/*   Updated: 2025/06/13 02:55:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exit the shell and free resources
int	builtin_exit(t_shell *shell)
{
	printf("exit\n");
	// free_shell(shell); to implement
	exit(0);
}
