/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/06/02 14:41:16 by stempels         ###   ########.fr       */
/*   Updated: 2025/05/28 13:22:23 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"

/* ************************************************************************** */
/*                                  MACROS                                    */
/* ************************************************************************** */
# define DELIMITERS " |&()\"<>\n"
/* MAKE SURE OPERATOR MACRO ORDER MATCH ENUM ORDER */
# define OPERATOR "|&<>()\"\n"
# define DOUBLE_ADJUST (OR_IF - OR)
# define SEPARATOR " "
# define IO_REDIRECTION LESS DLESS GREAT DGREAT
# define TYPE ((*token)->type)
# define N_TOKEN (TOKEN->next)
# define N_TYPE N_TOKEN->type
/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */
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

/* FILL ENUM IN THIS ORDER: SINGLE CHARACTER TOKENS THEN DOUBLE CHARACTER TOKENS */
/* MAKE SURE THE ORDER MATCH OPERATOR MACRO */
typedef enum e_type
{
/*0*/	WORD,
/*1*/	OR,
/*2*/	IF,
/*3*/	LESS,
/*4*/	GREAT,
/*5*/	LEFT_PAREN,
/*6*/	RIGHT_PAREN,
/*7*/	DQUOTE,
/*8*/	NEW_LINE,
/*9*/	OR_IF,
/*10*/	AND_IF,
/*11*/	DLESS,
/*12*/	DGREAT,
/*13*/	CMD,
/*14*/	FILENAME,
/*15*/	EOL,
/*16*/	ERROR,
/*17*/	SUBSHELL
}					t_type;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_token
{
	t_type		type;
	char		*start;
	size_t		size;
	struct s_token		*next;
}					t_token;

typedef union u_usage
{
	void	(*fct)();
	void	*content;
}		t_usage;

typedef struct s_node
{
	t_type				type;
	t_usage				use;
	struct s_node		*parent;
	struct s_node		*left;
	struct s_node		*right;
}					t_node;

t_node	*parser(t_token *token);
int	visit(t_node *tree, int indent);

//typedef struct s_shell
//{
	//const char		*cmds;
	//char			**envs;
	//struct s_token			*tokens;
	//t_token			*tree;
//}					t_shell;

//typedef int			(*t_fncmp)(void *a, void *b);

/* ************************************************************************** */
/*                                  SETUP                                     */
/* ************************************************************************** */

//int					ft_setup_signals(void);
//int					ft_isinteractive(void);
//t_shell				*ft_new_shell(char **envp);
//void				ft_minishell(t_shell *shell);

/* ************************************************************************** */
/*                                 DISPLAY                                    */
/* ************************************************************************** */

//const char			*ft_read_line(const char *prompt);
//void				ft_display_banner(void);
//void				ft_display_prompt(void);
//void				ft_logdebug(t_level level, const char *log);

/* ************************************************************************** */
/*                                 LEXER                                      */
/* ************************************************************************** */
t_token	*lexer(t_token **token_lst, char *cli);
void	show_lexeme(t_token *token_lst);
/**/
/* ************************************************************************** */
/*                                 PARSER                                     */
/* ************************************************************************** */


void	show_tree(t_node *tree, int indent);
/**/
/* ************************************************************************** */
/*                                 EXPANDER                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */

//int					ft_execute_tree(t_tree *tree);

/* ************************************************************************** */
/*                                  CLEANUP                                   */
/* ************************************************************************** */

//void				ft_free_cmds(const char *cmds);
//void				ft_free_arr(char **arr);
//void				ft_free_args(char **args);
//void				ft_free_tokens(t_token *tokens);
//void				ft_free_tree(t_tree *tree);
//void				ft_free_shell(t_shell *shell);

#endif /* MINISHELL_H */
