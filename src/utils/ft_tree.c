/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/12 19:57:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_args(char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
}

t_tree	*ft_new_tree(int type, char *cmd, char **args)
{
	t_tree	*tree;

	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = type;
	tree->cmd = ft_strdup(cmd);
	if (!tree->cmd)
		return (free(tree), NULL);
	tree->args = ft_stradup(args);
	if (!tree->args)
		return (free(tree->cmd), free(tree), NULL);
	tree->infile = -1;
	tree->outfile = -1;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int	ft_add2tree(void)
{
	return (SUCCESS);
}
