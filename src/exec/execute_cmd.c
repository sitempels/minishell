/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:09 by stempels          #+#    #+#             */
/*   Updated: 2025/06/17 16:15:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_node *tree, char **env)
{
	char	*path;
	char	**argv;

	if (tree->left)
		execute_descend(tree->left, env);
	argv = get_arg((tree->right)->use.content, 0, env_from_envp(env), 0);
	if (!argv)
		return (1);
	(tree->right)->use.arg = argv;
	path = get_path(argv[0], env, F_OK + X_OK);
	execve(path, argv, env);
	return (1);
}
