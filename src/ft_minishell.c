/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:35:40 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/13 00:51:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_minishell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_display_banner();
	while (1)
	{
		shell->cmds = ft_read_line("");
		if (!shell->cmds)
		{
			printf("%sLeaving the shell...\n", BOLD_RED);
			exit(0);
		}
		shell->tokens = ft_tokenize_cmds(shell->cmds);
		// shell->tree = ft_parse_tokens(shell->tokens);
		// if (!shell->tree)
		// 	break ;
		// if (!ft_execute_tree(shell->tree))
		// 	break ;
		ft_print_tokens(&shell->tokens);
		add_history(shell->cmds);
		if (shell->tokens)
			ft_free_tokens(shell->tokens);
		free((void *)shell->cmds);
	}
}
