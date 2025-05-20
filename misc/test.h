#ifndef TEST_H
# define TEST_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

//# define WORD 0
//# define CMD 1;

typedef	enum	s_type
{
	WORD,
	CMD
}		e_type;

typedef struct	s_node
{
	e_type		type;
	char		*content;
	struct s_node	*left;
	struct s_node	*right;
}			t_node;

typedef struct	s_token
{
	e_type		type;
	char		*content;
	struct s_token	*next;
}		t_token;

t_node	*parse_cmd(t_token *tokens);
#endif
