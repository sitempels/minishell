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

	if (!tree)
	{
		printf("TREE: NULL\n");
		return ;
	}
	if (indent == 1)
	{
		printf("\nPARSER OUTPUT: \n\n");
		printf("DESCENT		NODE_RANK	NODE_TYPE	CONTENT \n\n");
		printf("	");
	}
	printf("	  %d		  %s	", indent, get_enum(tree->type));
	i = 0;
	while (i < indent)	
	{
		printf("	");
		i++;
	}
	if (!tree->use.content)
		printf("  %s\n", get_enum(tree->type));
	else
		printf("  %.*s\n", (int)(tree->use.content)->size, (tree->use.content)->start);
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

static char *get_enum(int i)
{
	if (i == 0)
/*0*/		return ("WORD");
	if (i == 1)
/*1*/		return ("PIPE");
	if (i == 3)
/*3*/		return ("REDIRECT_I");
	if (i == 4)
/*4*/		return ("REDIRECT_O");
	if (i == 5)
/*5*/		return ("QUOTE");
	if (i == 6)
/*6*/		return ("DQUOTE");
	if (i == 7)
/*7*/		return ("SUBSHELL");
	if (i == 10)
/*10*/		return ("OR_IF");
	if (i == 11)
/*11*/		return ("AND_IF");
	if (i == 12)
/*12*/		return ("HERE_DOC");
	if (i == 13)
/*13*/		return ("DGREAT");
	if (i == 14)
/*14*/		return ("CMD");
	if (i == 15)
/*15*/		return ("FILENAME");
	if (i == 16)
/*16*/		return ("EOL");
	if (i == 17)
/*17*/		return ("ERROR");
	if (i == 18)
/*18*/		return ("SUBSHELL");
	return (NULL);
}
