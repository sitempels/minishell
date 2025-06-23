/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:33 by sjacquet          #+#    #+#             */
/*   Updated: 2025/06/23 09:21:08 by stempels         ###   ########.fr       */
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
# define SEPARATOR " "
# define IFS " "
/* 0 or less prevent HERE_DOC creation */
# define MAX_HEREDOC 50
/**/
/*_________________________________ENUM_______________________________________*/
/**/
typedef enum e_errnum
{
	N_PRINT,
	CREAT_FILE,
	OPEN_FILE,
	CLOSE_FILE,
	N_CREAT,
	NOT_H,
	I_MISS,
	O_MISS,
}		t_errnum;

typedef enum e_descend
{
	LEFT,
	RIGHT
}					t_descend;

/* FILL ENUM IN THIS ORDER: SINGLE CHARACTER THEN DOUBLE CHARACTER TOKENS */
/* MAKE SURE THE ORDER MATCH OPERATOR MACRO */
typedef enum e_type
{
	WORD,  /*0*/
	OR,    /*1*/
	IF,    /*2*/
	LESS,  /*3*/
	GREAT, /*4*/
	//	QUOTE,			/*5*/
	//	DQUOTE,			/*6*/
	LEFT_PAREN,  /*7*/
	RIGHT_PAREN, /*8*/
	NEW_LINE,    /*9*/
	EOL,         /*16*/
	OR_IF,       /*10*/
	AND_IF,      /*11*/
	DLESS,       /*12*/
	DGREAT,      /*13*/
	CMD,         /*14*/
	FILENAME,    /*15*/
	ERROR,       /*17*/
	SUBSHELL,    /*18*/
	ARGUMENT,    /*19*/
}					t_type;

/**/
/*_________________________________STRUCT_____________________________________*/
/**/

typedef union u_usage
{
	int				(*fct)();
	char			**arg;
	struct s_token	*content;
}					t_usage;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	enum e_type			type;
	char			*start;
	size_t			size;
	struct s_token	*next;
}					t_token;

typedef struct s_node
{
	t_type			type;
	t_usage			use;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_shell
{
	char			*cli;
	t_env			*env;
	t_token			*tokens;
	t_node			*tree;
	int				mode;
	int				status;
}					t_shell;
/*_________________________________SETUP______________________________________*/
void				signals(void);
t_shell				*init_shell(int mode, char **envp);

/*__________________________________ENV_______________________________________*/
t_env				*new_env(char *env);
t_env				*env_from_envp(char **envp);
char				*envp_getone(t_env *env);
char				**envp_from_env(t_env *env);
t_env				*env_getlast(t_env *lst);
t_env				*env_getone(t_env *head, char *key, size_t len);
char				*env_getpath(t_env *env);
char				**env_getallpaths(char *path);
int					env_addfront(t_env **head, t_env *new);
char				*extract_key(char *env);
char				*extract_value(char *env);
int					envp_size(char **envp);
size_t				env_size(t_env *env);
void				env_freeone(t_env *env);
void				env_freeall(t_env *env);
int					env_updateone(t_env **head, char *key, char *value);
int					env_addback(t_env **head, t_env *new);
int					env_delone(t_env **head, char *key);
int					env_sortkey(t_env **head);
t_env				*env_dup(t_env *src);

/*_________________________________BUILTINS___________________________________*/
void				builtin_env(t_env *env);

/*_________________________________DISPLAY____________________________________*/
void				display_banner(void);
void				display_prompt(void);
/*__________________________________LEXER_____________________________________*/
int			is_valid_cli(const char *cli);
t_token		*lexer(t_shell *shell, t_token **token_lst, char *cli);
t_token		*handle_heredoc(t_shell *shell, t_token *end);

/*____________UTILS_____________*/
t_token				*token_addback(t_token **tokens, t_token *new);
t_token				*token_create(int type, char *start, size_t size);
t_token				*token_last(t_token **token_lst);

/*_________________________________PARSER_____________________________________*/
t_node				*parser(t_shell *shell, t_token **token);
t_node				*parse_pipeline(t_shell *shell, t_token **token);
t_node				*parse_complete_cmd(t_shell *shell, t_token **token);

/*____________CMD_______________*/
t_node				*parse_cmd(t_shell *shell, t_token **token);
t_node				*parse_simple_cmd(t_shell *shell, t_token **token);
t_node				*parse_io_redirect(t_shell *shell, t_token **token);

/*____________UTILS_____________*/
t_node				*create_node(t_shell *shell, t_token **token, int type);
t_token				*munch_token(t_token **token, int clean);
t_node				*node_addback(t_node *node, t_node *new, int mode);
/**/
/*_________________________________EXPAND_____________________________________*/
void				*expander(t_token *token);
/**/
/*_________________________________EXEC_______________________________________*/
int		execute_and_or_if(t_shell *shell, t_node *tree, char **env);
int		execute_subshell(t_shell *shell, t_node *tree, char **env);
int		execute_pipe(t_shell *shell, t_node *tree, char **env);
int		execute_cmd(t_shell *shell, t_node *tree, char **env);
/**/
/*____________REDIR_____________*/
int		execute_redir_input(t_shell *shell, t_node *tree, char **env);
int		execute_redir_output(t_shell *shell, t_node *tree, char **env);
int		execute_redir_output_a(t_shell *shell, t_node *tree, char **env);
/**/
/*____________UTILS_____________*/
int		execute_node(t_shell *shell, t_node *tree, char **env);
int		create_fork(t_shell *shell, pid_t *pid);
int		create_pipe(int *nbr, t_shell *shell, int *pipefd, pid_t *pid);
char	**get_arg(t_token *arg, int nbr, t_env *env, int status);
char	*process_arg(t_token *arg, t_env *env, int status);
/**/
/*_________________________________UTILS______________________________________*/
char				*get_path(char *cmd, char **env, int mode);
/**/
/*_________________________________CLEAN______________________________________*/
void	ft_error(t_shell *shell, int nbr_error, ...);
char	*get_errnum(int	error);
char	**free_array(char **array, int pos);
void	clean_token_lst(t_token **token_lst);
void	clean_tree(t_node **tree);
void	clean_shell(t_shell *shell);
/**/
/*_________________________________DEBUG______________________________________*/
/**/
int					visit(t_node *tree, int indent);
void				show_lexeme(t_token *token_lst);
void				show_tree(t_node *tree, int indent);
/**/
#endif
