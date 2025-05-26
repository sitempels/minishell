/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:41:26 by stempels          #+#    #+#             */
/*   Updated: 2025/05/26 11:35:47 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token	*token_lst;
	t_node	*tree;

	if (argc != 2)
		return (write(1, "Error Arg!\n", 10));
	token_lst = NULL;
	token_lst = *lexer(&token_lst, argv[1]);	
	tree = parser(token_lst);
	visit(tree, 0);
	return (0);
}

int	visit(t_node *tree, int indent)
{
	int	i;

	i = 0;
	if (!tree)
		return (0);
	while (i < indent)	
	{
		printf("\t");
		i++;
	}
	printf("NODE_TYPE: %d,	CONTENT: %s\n", tree->type, (char *)tree->use.content);
	if (tree->left)
		visit(tree->left, indent + 1);
	if (tree->right)
		visit(tree->right, indent + 1);
	return (0);
}
