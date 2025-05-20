#include "test.h"

int	visit(t_node *tree, int indent);

int	main(void)
{
	t_token	*temp;
	t_token	*cmdname;
	t_token	*cmdarg;
	t_token	*cmdarg1;
	t_token	*cmdarg2;
	t_node	*tree;

	cmdname = (t_token *) malloc(sizeof(t_token) * 1);	
	cmdarg = (t_token *) malloc(sizeof(t_token) * 1);	
	cmdarg1 = (t_token *) malloc(sizeof(t_token) * 1);	
	cmdarg2 = (t_token *) malloc(sizeof(t_token) * 1);	
	cmdname->type = WORD;
	cmdname->content = "ls";
	cmdname->next = cmdarg;
	cmdarg->type = WORD;
	cmdarg->content = "ahwlkghkawh/g;khaw";
	cmdarg->next = cmdarg1;
	cmdarg1->type = WORD;
	cmdarg1->content = "357553453318843400542";
	cmdarg1->next = cmdarg2;
	cmdarg2->type = WORD;
	cmdarg2->content = "ASLKHGL?KHAGKLH";
	cmdarg2->next = NULL;
	tree = parse_cmd(cmdname);
	temp = cmdname;
	while (temp)
	{
		printf("TOKEN_TYPE: %d,	CONTENT: %s\n", temp->type, temp->content);
		temp = temp->next;
	}
	visit(tree, 0);
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
	printf("NODE_TYPE: %d,	CONTENT: %s\n", tree->type, tree->content);
	if (tree->left)
		visit(tree->left, indent + 1);
	if (tree->right)
		visit(tree->right, indent + 1);
	return (0);
}
