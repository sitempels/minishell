/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:14:43 by stempels          #+#    #+#             */
/*   Updated: 2025/07/05 14:19:58 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_io(t_shell *shell)
{
	int	fd;

	fd = open(shell->std_io[0], O_RDWR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	fd = open(shell->std_io[1], O_RDWR);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
