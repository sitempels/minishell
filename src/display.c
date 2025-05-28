/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:53:15 by stempels          #+#    #+#             */
/*   Updated: 2025/05/21 16:57:41 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(void);

void	ft_display_banner(void)
{
	const char	*b;

	b = "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		"Buidl by Simon T. && Selim J.\n";
	printf(MAGENTA);
	printf("\n\n");
	printf("%s", b);
	printf("\n\n");
	printf(RESET);
}

void	ft_display_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;
	char	*tty;
	int		ttys;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	fcwd = ft_strrpl(cwd, home, "~");
	tty = ttyname(STDIN_FILENO);
	ttys = ttyslot();
	printf("📁 %s%s 💻 %s%s 🎰 %s%d\n%s%c%s ", BOLD_CYAN, fcwd, BOLD_MAGENTA, tty,
		BOLD_YELLOW, ttys, BOLD_GREEN, '$', RESET);
	free(cwd);
	free(fcwd);
}

const char	*ft_read_line(const char *prompt)
{
	char	*cmds;

	ft_display_prompt();
	cmds = readline(prompt);
	if (!cmds)
		return (NULL);
	return (cmds);
}
/*
t_shell	*ft_new_shell(char **envs)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmds = NULL;
	shell->envs = ft_stradup(envs);
	if (!shell->envs)
		return (NULL);
	shell->tokens = NULL;
	shell->tree = NULL;
	return (shell);
}
*/
int	main(void)
{
	ft_minishell();
	return (0);
}

t_node	**parse(t_token **tokens)
{
	t_node	**tree;

	*tree = parse_cmd(*tokens);
	return (tree);
}

void	ft_minishell(void)
{
	int	j;
	char	*line;
	t_token	**token_lst;
	t_token	*temp;
	t_node	**tree;

	//if (!shell)
	//	return ;
//	ft_display_banner();
	while (1)
	{
		line = "ls test ls ls";
//		line = ft_read_line("");
//		if (!shell->cmds)
//		{
//			printf("%sLeaving the shell...\n", BOLD_RED);
//			exit(0);
//		}
//		shell->tokens = ft_tokenize_cmds(shell->cmds);
		// shell->tree = ft_parse_tokens(shell->tokens);
		// if (!shell->tree)
		// 	break ;
		// if (!ft_execute_tree(shell->tree))
		// 	break ;
//		ft_print_tokens(&shell->tokens);
//		add_history(shell->cmds);
//		if (shell->tokens)
//		"	ft_free_tokens(shell->tokens);
		token_lst = lexer(line);
		temp = *token_lst;	
		while (temp)
		{
			printf("TOKEN_TYPE: %d	",temp->type);
			printf("TOKEN_CONTENT: ");
			j = 0;
			while (j < temp->size)
			{
				write(1, &(temp->start[j]), 1);
				j++;
			}
			temp = temp->next;
		}
		tree = parse(token_lst);
		visit(*tree, 0);
		break ;
//		free((void *)shell->cmds);
	}
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
	printf("NODE_TYPE: %d,	CONTENT: %s\n", tree->type, (char *)tree->use.content);
	if (tree->left)
		visit(tree->left, indent + 1);
	if (tree->right)
		visit(tree->right, indent + 1);
	return (0);
}
