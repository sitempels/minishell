/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/12 20:24:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	extern char	**environ;
	t_shell		*shell;

	ft_setup_signals();
	shell = ft_new_shell(environ);
	if (!shell)
	{
		ft_putstr_fd("minishell: failed to initialize shell\n", STDERR_FILENO);
		return (FAILURE);
	}
	ft_minishell(shell);
	ft_free_shell(shell);
	return (SUCCESS);
}
