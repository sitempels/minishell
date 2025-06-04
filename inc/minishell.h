/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/06/04 18:19:45 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"

/**/
/*_________________________________MACRO______________________________________*/
/**/
# define DELIMITERS " |&()<>\n\t\0"
/* MAKE SURE OPERATOR MACRO ORDER MATCH ENUM ORDER */
# define OPERATOR "|&<>()"
# define DOUBLE_ADJUST (OR_IF - OR) /*equivalent to (OR_IF - OR) but cannot 'cause norme */
# define SEPARATOR " "
/**/
/*_________________________________ENUM_______________________________________*/
/**/
typedef enum e_descend
{
	LEFT,
	RIGHT
}		t_descend;

typedef enum e_level
{
	DEBUG,
	INFO,
	WARN,
}					t_level;

/* FILL ENUM IN THIS ORDER: SINGLE CHARACTER THEN DOUBLE CHARACTER TOKENS */
/* MAKE SURE THE ORDER MATCH OPERATOR MACRO */
typedef enum e_type
{
	WORD,			/*0*/
	OR,			/*1*/
	IF,			/*2*/
	LESS,			/*3*/
	GREAT,			/*4*/
//	QUOTE,			/*5*/
//	DQUOTE,			/*6*/
	LEFT_PAREN,		/*7*/
	RIGHT_PAREN,		/*8*/
	NEW_LINE,		/*9*/
	OR_IF,			/*10*/
	AND_IF,			/*11*/
	DLESS,			/*12*/
	DGREAT,			/*13*/
	CMD,			/*14*/
	FILENAME,		/*15*/
	EOL,			/*16*/
	ERROR,			/*17*/
	SUBSHELL,		/*18*/
	ARGUMENT,		/*19*/
}					t_type;

/**/
/*_________________________________STRUCT_____________________________________*/
/**/

typedef struct s_token
{
	t_type			type;
	char			*start;
	size_t			size;
	struct s_token	*next;
}				t_token;

typedef union u_usage
{
	int	(*fct)();
	char	**arg;
	t_token	*content;
}		t_usage;

typedef struct s_node
{
	t_type			type;
	t_usage			use;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;
/*_________________________________SETUP______________________________________*/
/*_________________________________DISPLAY____________________________________*/
/*_________________________________LEXER______________________________________*/
t_token	*lexer(t_token **token_lst, char *cli);

/*____________UTILS_____________*/
t_token	*token_addback(t_token **tokens, t_token *new);
t_token	*token_create(int type, char *start, size_t size);
t_token	*token_last(t_token **token_lst);

/*_________________________________PARSER_____________________________________*/
t_node	*parser(t_token *token);
t_node	*parse_pipeline(t_token **token);

/*____________CMD_______________*/
t_node	*parse_cmd(t_token **token);
t_node	*parse_simple_cmd(t_token **token);
t_node	*parse_word(t_token **token);

/*____________REDIRECT__________*/
t_node	*parse_cmd_affix(t_token **tokens);
t_node	*parse_io_redirect(t_token **token);
t_node	*parse_io_here(t_token **token);
t_node	*parse_io_file(t_token **token);
t_node	*parse_filename(t_token **token);

/*____________UTILS_____________*/
t_node	*create_node(t_token **token, int type);
t_token	*munch_token(t_token **token);
t_node	*node_addback(t_node *node, t_node *new, int mode);
/**/
/*_________________________________EXPAND_____________________________________*/
void	*expander(t_token *token);
/**/
/*_________________________________EXEC_______________________________________*/
/**/
int	execute(t_node *tree, char **env);
int	execute_cmd(t_node *tree, char **env);

/*____________UTILS_____________*/
char	**get_arg(t_token *arg, int nbr);
char	*process_arg(t_token *arg);
/**/
/*_________________________________UTILS______________________________________*/
/**/
char	**free_array(char **array, int pos);
char	*path_cmd(char *cmd, char **env);
/**/
/*_________________________________CLEAN______________________________________*/
/**/
/**/
/*_________________________________DEBUG______________________________________*/
/**/
int		visit(t_node *tree, int indent);
void	show_lexeme(t_token *token_lst);
void	show_tree(t_node *tree, int indent);
/**/
#endif /* MINISHELL_H */
