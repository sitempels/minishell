#include "minishell.h"

static char *get_enum(int i);

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
		temp = temp->next;
	}
	printf("\n");
	return ;
}

void	show_tree(t_node *tree, int indent)
{
	int	i;
	t_token	*tmp;

	if (!tree)
	{
		printf("TREE: NULL\n");
		return ;
	}
	if (indent == 1)
	{
		printf("\nPARSER OUTPUT: \n\n");
		printf("DESCENT\t\tNODE_RANK\tNODE_TYPE\t\tCONTENT \n\n");
		printf("\t");
	}
	printf("\t%d\t\t%s\t", indent, get_enum(tree->type));
	i = 0;
	while (i < indent)	
	{
		printf("\t");
		i++;
	}
	if (!tree->use.content)
		printf("  %s\n", get_enum(tree->type));
	else if (tree->type == FILENAME || tree->type == ARGUMENT)
	{
		if (tree->type == ARGUMENT)	
		{
			tmp = tree->use.content;
			while (tmp)
			{
				printf("\t%.*s ", (int)tmp->size, tmp->start);
				tmp = tmp->next;
			}
		if (tree->type == FILENAME)
			printf("\t%s ", (tree->use.arg)[0]);
		}
		printf("\n");
	}
	else
	{
		printf("\t%s", get_enum(tree->type));
		printf("\n");
	}
	if (tree->left)
	{
		printf("LEFT\t");
		show_tree(tree->left, indent + 1);
	}
	if (tree->right)
	{
		printf("RIGHT\t");
		show_tree(tree->right, indent + 1);
	}
	return ;
}

static char *get_enum(int i)
{
	if (i == WORD)
/*0*/		return ("WORD");
	if (i == OR)
/*1*/		return ("PIPE");
	if (i == LESS)
/*3*/		return ("REDIRECT_I");
	if (i == GREAT)
/*4*/		return ("REDIRECT_O");
	if (i == LEFT_PAREN)
/*7*/		return ("SUBSHELL");
	if (i == OR_IF)
/*10*/		return ("OR_IF");
	if (i == AND_IF)
/*11*/		return ("AND_IF");
	if (i == DLESS)
/*12*/		return ("HERE_DOC");
	if (i == DGREAT)
/*13*/		return ("REDIRECT_O_A");
	if (i == CMD)
/*14*/		return ("CMD");
	if (i == FILENAME)
/*15*/		return ("FILENAME");
	if (i == EOL)
/*16*/		return ("EOL");
	if (i == ERROR)
/*17*/		return ("ERROR");
	if (i == SUBSHELL)
/*18*/		return ("SUBSHELL");
	if (i == ARGUMENT)
/*19*/		return ("ARGUMENT");
	return (NULL);
}
