/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:37:26 by user              #+#    #+#             */
/*   Updated: 2025/07/09 16:16:27 by sjacquet         ###   ########.fr       */
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
			printf("pwd: not enough memory (ENOMEM)\n");
		else if (errno == ENOENT)
			printf("pwd: this directory no longer exists (ENOENT)\n");
		else if (errno == EACCES)
			printf("pwd: permission denied (EACCES)\n");
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
