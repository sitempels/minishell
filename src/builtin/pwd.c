/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:37:26 by user              #+#    #+#             */
/*   Updated: 2025/07/03 04:55:27 by user             ###   ########.fr       */
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
			return (printf("pwd: not enough memory (ENOMEM)\n"), 12);
		else if (errno == ENOENT)
			return (printf("pwd: this directory no longer exists (ENOENT)\n"),
				2);
		else if (errno == EACCES)
			return (printf("pwd: permission denied (EACCES)\n"), 13);
		else
			return (perror("pwd"), 1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
