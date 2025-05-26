#include "minishell.h"

int	main(int argc, char **argv)
{
	t_token	*token_lst;
	t_token	*temp;

	if (argc != 2)
		return (write(1, "Too many arg!\n", 14));
	token_lst = NULL;
	token_lst = *lexer(&token_lst, argv[1]);
	temp = token_lst;	
	while (temp)
	{
		printf("TOKEN_TYPE: %d	%*s\n",temp->type, (int)temp->size, temp->start);
		printf("temp->size: %d \n", (int)temp->size);
		temp = temp->next;
	}
	return (0);
}
