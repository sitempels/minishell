/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:09 by stempels          #+#    #+#             */
/*   Updated: 2025/06/09 10:06:24 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	execute_cmd(t_node *tree, char **env)
{
	int		pid;
	char	*path;
	char	**argv;

	argv = get_arg((tree->right)->use.content, 0);
	if (!argv)
		return (1); //free rest of the t_tokens
	(tree->right)->use.arg = argv;
	path = get_path(argv[0], env, F_OK + X_OK); 
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		execve(path, argv, env);
		return (1);
	}
	else
		waitpid(pid);
	return (0);
}

char	**get_arg(t_token *arg, int nbr)
{
	char	**argv;

	if (!arg)
	{
		argv = (char **) ft_calloc(nbr + 1, sizeof(char *));
		if (!argv)
			return (NULL);
		return (argv);
	}
	argv = get_arg(arg->next, nbr + 1);
	if (!argv)
		return (NULL);
	argv[nbr] = process_arg(arg);
	if (!argv[nbr])
		return (NULL);
	return (argv);
}

char	*process_arg(t_token *arg)
{
	size_t	i;
	char	*str;
	size_t	size;

//	size = calc_expand(arg);
	size = arg->size;
//	str = fill_expand(arg, str);
	str = (char *) ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = (arg->start)[i];
		i++;
	}
	return (str);
}
