/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 19:38:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"

typedef enum e_level
{
	DEBUG,
	INFO,
	WARN,
	ERROR
}					t_level;

typedef enum e_type
{
	VOID,
	WORD,
	PIPE,
	AMPERSAND,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PAREN_LEFT,
	PAREN_RIGHT,
	WILDCARD,
	ENV,
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*token;
	struct s_token	*next;
}					t_token;

typedef enum e_node
{
	CMDX,
	JOBX,
	PIPEX,
	IFX,
}					t_node;

typedef struct s_tree
{
	int				type;
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	struct s_tree	*right;
	struct s_tree	*left;
}					t_tree;

typedef struct s_shell
{
	const char		*cmds;
	char			**envs;
	t_token			*tokens;
	t_tree			*tree;
}					t_shell;

int					ft_setup_signals(void);
int					ft_isinteractive(void);

t_shell				*ft_new_shell(char **envp);
int					ft_minishell(t_shell *shell);

const char			*ft_read_line(const char *prompt);
void				ft_display_banner(void);
void				ft_display_prompt(void);

t_token				*ft_new_token(t_type type, char *value);
t_token				*ft_last_token(t_token **tokens);
int					ft_add_token(t_token **tokens, t_token *token);
void				ft_print_tokens(t_token **tokens);
t_token				*ft_tokenize_cmds(const char *cmds);

int					ft_handl_word(t_token **tokens, const char *cmds, int *i);
int					ft_handl_oper(t_token **tokens, const char *cmds, int *i);
int					ft_handl_pipe(t_token **tokens, const char *cmds, int *i);
int					ft_handl_amper(t_token **tokens, const char *cmds, int *i);
int					ft_handl_redir(t_token **tokens, const char *cmds, int *i);
int					ft_handl_paren(t_token **tokens, const char *cmds, int *i);
int					ft_handl_wild(t_token **tokens, const char *cmds, int *i);
int					ft_handl_env(t_token **tokens, const char *cmds, int *i);

t_tree				*ft_new_tree(int type, char *cmd, char **args);
int					ft_add2tree(void);
t_tree				*ft_parse_tokens(t_token *tokens);

int					ft_execute_tree(t_tree *tree);

void				ft_logdebug(t_level level, const char *log);

void				ft_free_cmds(const char *cmds);
void				ft_free_arr(char **arr);
void				ft_free_args(char **args);
void				ft_free_tokens(t_token *tokens);
void				ft_free_tree(t_tree *tree);
void				ft_free_shell(t_shell *shell);

#endif
