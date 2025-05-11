/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 19:26:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_shell		*shell;
	extern char	**environ;

	shell = ft_new_shell(environ);
	if (!shell)
		return (FAILURE);
	ft_setup_signals();
	ft_minishell(shell);
	ft_free_shell(shell);
	return (SUCCESS);
}
