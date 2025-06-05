/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:57:50 by stempels          #+#    #+#             */
/*   Updated: 2025/06/05 12:10:48 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_node *tree, char **env)
{
	if (!tree)
		return (1);
	if (tree->type == CMD)
	{
		if (tree->right)
			execute(tree->right, env);
		tree->use.fct(tree, env);
		return (1);
	}
	tree->use.fct(tree, env);
	if (tree)
	{
		if (tree->left)
			execute(tree->left, env);
		if (tree->right)
			execute(tree->right, env);
	}
	return (0);
}

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
