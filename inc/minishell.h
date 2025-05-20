/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/16 18:30:00 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"

/* ************************************************************************** */
/*                                  MACROS                                    */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

typedef enum e_level
{
	DEBUG,
	INFO,
	WARN,
}					t_level;

typedef enum e_type
{
	WORD = 1,
	NEWLINE,
	AND_IF,
	OR_IF,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	EOL,
}					t_type;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_token
{
	t_type		type;
	char		*start;
	size_t		size;
	struct s_token		*prev;
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

typedef struct s_shell
{
	const char		*cmds;
	char			**envs;
	struct s_token			*tokens;
	t_tree			*tree;
}					t_shell;

typedef int			(*t_fncmp)(void *a, void *b);

/* ************************************************************************** */
/*                                  SETUP                                     */
/* ************************************************************************** */

int					ft_setup_signals(void);
int					ft_isinteractive(void);
t_shell				*ft_new_shell(char **envp);
void				ft_minishell(t_shell *shell);

/* ************************************************************************** */
/*                                 DISPLAY                                    */
/* ************************************************************************** */

const char			*ft_read_line(const char *prompt);
void				ft_display_banner(void);
void				ft_display_prompt(void);
void				ft_logdebug(t_level level, const char *log);

/* ************************************************************************** */
/*                                 TOKENIZER                                  */
/* ************************************************************************** */

t_token				*ft_new_token(t_type type, char *value);
t_token				*ft_last_token(t_token **tokens);
int					ft_add_token(t_token **tokens, t_token *token);
void				ft_print_tokens(t_token **tokens);
t_token				*ft_tokenize_cmds(const char *cmds);

/* Token handlers */
int					ft_handl_word(t_token **tokens, const char *cmds, int *i);
int					ft_handl_oper(t_token **tokens, const char *cmds, int *i);
int					ft_handl_pipe(t_token **tokens, const char *cmds, int *i);
int					ft_handl_amper(t_token **tokens, const char *cmds, int *i);
int					ft_handl_redir(t_token **tokens, const char *cmds, int *i);
int					ft_handl_paren(t_token **tokens, const char *cmds, int *i);
int					ft_handl_wild(t_token **tokens, const char *cmds, int *i);
int					ft_handl_env(t_token **tokens, const char *cmds, int *i);

/* ************************************************************************** */
/*                                 PARSER                                     */
/* ************************************************************************** */

t_tree				*ft_new_tree(int type, char *cmd, char **args);
int					ft_add2tree(void);
t_tree				*ft_parse_tokens(t_token *tokens);

/* ************************************************************************** */
/*                                 EXPANDER                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */

int					ft_execute_tree(t_tree *tree);

/* ************************************************************************** */
/*                                  CLEANUP                                   */
/* ************************************************************************** */

void				ft_free_cmds(const char *cmds);
void				ft_free_arr(char **arr);
void				ft_free_args(char **args);
void				ft_free_tokens(t_token *tokens);
void				ft_free_tree(t_tree *tree);
void				ft_free_shell(t_shell *shell);

#endif /* MINISHELL_H */
