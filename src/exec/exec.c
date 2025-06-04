/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/04 18:21:11 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_node *tree, char **env)
{
	if (!tree)
		return (1);
	tree->use.fct();
	if (tree)
	{
		if (tree->left)
			execute(tree->left, env);
		if (tree->right)
			execute(tree->right, env);
	}
	return (0);
}

int	execute_cmd(t_node *tree, char **env)
{
	char	*path;
	char	**argv;

	argv = get_arg((tree->right)->use.content, 0);
	if (!argv)
		return (1); //free rest of the t_tokens
	tree->use.arg = argv;
	path = path_cmd(argv[0], env); 
	execv(path, argv);
	return (1);
}

char	**get_arg(t_token *arg, int nbr)
{
	char	**argv;

	if (!arg)
	{
		argv = (char **) ft_calloc(nbr + 2, sizeof(char *));
		if (!argv)
			return (NULL);
	}
	argv = get_arg(arg->next, nbr + 1);
	if (!argv)
		return (free_array(argv, nbr + 1));
	argv[nbr] = process_arg(arg);
	if (!argv[nbr])
		return (NULL);
	return (argv);
}

char	*process_arg(t_token *arg)
{
	int	i;
	char	*str;
	size_t	size;

	size = arg->size;
//	size = calc_expand(arg);
	str = (char *) ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while ((arg->start)[i])
	{
		str[i] = (arg->start)[i];
		i++;
	}
//	str = fill_expand(arg, str);
	free(arg);
	return (str);
}

/*
size_t	calc_expand(t_token *arg)
{
	int	j;
	char	*str;
	size_t	len;

	str = (arg->start);
	len = (arg->size);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$') 
		{
			j = 0;
			while (str[i + j] && str[i + j] != " ")
				j++;
			len = i - j + get_expand_len(str[i + 1], j - 1); //-->need envi there
		}
		i++;
	}
	return (len);
}
*/

char	**free_array(char **array, int pos)
{
	if (!array)
		return (NULL);	
	while (array[pos])
	{
		if (array[pos])
		{
			free(array[pos]);
			array[pos] = NULL;
		}
		pos++;
	}
	return (NULL);
}
