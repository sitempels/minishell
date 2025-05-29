/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:31:42 by stempels          #+#    #+#             */
/*   Updated: 2025/05/29 14:49:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_lexeme(t_token *token_lst);
void	show_tree(t_node *tree, int indent);

int	main(int argc, char **argv)
{
	int	i;
	t_token	*token_lst;
	t_node	*tree;

	if (argc < 2 || argc > 3)
		return (write(1, "Error Arg!\n", 10));
	i = argc - 1;
	token_lst = NULL;
	token_lst = *lexer(&token_lst, argv[i]);	
	if (i == 2 && (argv[1][0] == '1' || argv[1][0] == '3'))
	{
		show_lexeme(token_lst);
		if (argv[1][0] == '1')
			return (0);
	}
	tree = parser(token_lst);
	if (i == 2 && (argv[1][0] == '2' || argv[1][0] == '3'))
		show_tree(tree, 1);
	return (0);
}

void	show_lexeme(t_token *token_lst)
{
	t_token	*temp;

	temp = token_lst;	
	if (!token_lst)
	{
		printf("TOKEN_LST: NULL");
		return ;
	}
	printf("\nLEXER OUTPUT: \n\n");
	while (temp)
	{
		if (temp->type == EOL)
			printf("TOKEN_TYPE: %d	%s\n",temp->type, "EOL");
		else
			printf("TOKEN_TYPE: %d	%.*s\n",temp->type, (int)temp->size, temp->start);
//		printf("temp->size: %d \n", (int)temp->size);
		temp = temp->next;
	}
	printf("\n");
	return ;
}

void	show_tree(t_node *tree, int indent)
{
	int	i;

	if (!tree)
	{
		printf("TREE: NULL");
		return ;
	}
	if (indent == 1)
	{
		printf("\nPARSER OUTPUT: \n\n");
		printf("DESCENT		NODE_RANK	NODE_TYPE	CONTENT \n\n");
		printf("	");
	}
	printf("	  %d		  %d	", indent, tree->type);
	i = 1;
	while (i < indent)	
	{
		printf("	");
		i++;
	}
	printf("  %s\n", (char *)tree->use.content);
	if (tree->left)
	{
		printf("LEFT	");
		show_tree(tree->left, indent + 1);
	}
	if (tree->right)
	{
		printf("RIGHT	");
		show_tree(tree->right, indent + 1);
	}
	return ;
}
