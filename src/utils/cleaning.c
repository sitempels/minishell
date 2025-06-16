/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:14:47 by stempels          #+#    #+#             */
/*   Updated: 2025/06/16 13:02:02 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tree(t_node **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->left)
		clean_tree(&(*tree)->left);
	if ((*tree)->right)
		clean_tree(&(*tree)->right);
	free(*tree);
	*tree = NULL;
	return ;
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

void	clean_token_lst(t_token **token_lst)
{
	if (!token_lst || !*token_lst)
		return ;
	if ((*token_lst)->next)
		clean_token_lst(&(*token_lst)->next);
	*token_lst = NULL;
	return ;
}
