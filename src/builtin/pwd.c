/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:37:26 by user              #+#    #+#             */
/*   Updated: 2025/07/10 17:05:11 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return status code:
// ENOMEM code:12 not enough memory
// ENOENT code:2 no such file or directory
// EACCES code:13 permission denied
int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (errno == ENOMEM)
			ft_putendl_fd("pwd: not enough memory", 2);
		else if (errno == ENOENT)
			ft_putendl_fd("pwd: current directory does not exist", 2);
		else if (errno == EACCES)
			ft_putendl_fd("pwd: permission denied", 2);
		else
			perror("pwd");
		if (errno)
			return (errno);
		else
			return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
