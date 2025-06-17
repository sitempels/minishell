/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:14:47 by stempels          #+#    #+#             */
/*   Updated: 2025/06/17 14:55:50 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_errnum(int	error);

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
	free(*token_lst);
	*token_lst = NULL;
	return ;
}

static char	*get_errnum(int	error)
{
	if (error == N_PRINT)
		return ("");
	if (error == CREAT_FILE)
		return ("Could not create file");
	if (error == OPEN_FILE)
		return ("Could not open file");
	if (error == CLOSE_FILE)
		return ("could not close file");
	if (error == CREAT_TOKEN)
		return ("Could not create token");
	if (error == CREAT_NODE)
		return ("Could not create node");
	if (error == MISS)
		return ("file missing");
	if (error == NOT_H)
		return ("not handled");
	return (NULL);
}

void	ft_error(t_shell *shell, char *context, int error)
{
	if (context)
		printf("MINISHELL ERROR: %s %s \n", context, get_errnum(error));
	clean_shell(shell);
}

void	clean_shell(t_shell *shell)
{
	if (shell->tokens)
		clean_token_lst(&shell->tokens);
	shell->tokens = NULL;
	if (shell->tree)
		clean_tree(&shell->tree);
	shell->tree = NULL;
	exit (1);
}
