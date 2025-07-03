/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:05:48 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:06:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_errnum(int error)
{
	if (error == N_PRINT)
		return ("");
	if (error == CREAT_FILE)
		return ("Could not create file");
	if (error == OPEN_FILE)
		return ("Could not open file");
	if (error == CLOSE_FILE)
		return ("could not close file");
	if (error == N_CREAT)
		return ("Could not create");
	if (error == C_MISS)
		return ("Command not found");
	if (error == A_MISS)
		return ("Argument missing");
	if (error == I_MISS)
		return ("Input file missing");
	if (error == O_MISS)
		return ("Output file missing");
	if (error == NOT_H)
		return ("not handled");
	if (error == NEAR)
		return ("syntax error near unexpected token ");
	return (NULL);
}

int	ft_error(t_shell *shell, int quit, int nbr_context, ...)
{
	char	*error;
	va_list	error_msg;

	if (nbr_context > 0)
	{
		write(2, "minishell: ", 11);
		va_start(error_msg, nbr_context);
		while (nbr_context > 0)
		{
			error = va_arg(error_msg, char *);
			write(2, error, ft_strlen(error));
			nbr_context--;
		}
		write(2, "\n", 1);
		va_end(error_msg);
	}
	if (quit)
	{
		if (errno != 0)
			builtin_exit(shell, 0, errno);
		builtin_exit(shell, 0, shell->status);
	}
	clean_shell(shell);
	return (shell->status);
}
