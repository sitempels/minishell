/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/06/10 04:14:04 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Implement the new t_shell structure
int	minishell(int mode, char **env)
{
	pid_t	pid;
	t_shell	*shell;

	signals();
	display_banner();
	shell = init_shell(mode, env);
	while (1)
	{
		shell->tokens = NULL;
		shell->tree = NULL;
		display_prompt();
		shell->cli = readline("\033[1;32m$\033[0m ");
		if (!shell->cli)
		{
			printf("%sLEAVING the minishell...\n", BOLD_RED);
			break ;
		}
		add_history(shell->cli);
		shell->tokens = lexer(&shell->tokens, shell->cli);
		if (!shell->tokens)
			return (1);
		if (mode == 1 || (mode >= 2 && mode != 4))
			show_lexeme(shell->tokens);
		shell->tree = parser(shell->tokens);
		if (!shell->tree)
			return (1);
		if (mode == 1 || mode >= 3)
			show_tree(shell->tree, 1);
		if (mode <= 1)
		{
			pid = fork();
			if (pid < 0)
				return (1);
			else if (pid == 0)
				execute(shell->tree, env);
			else
				wait(&pid);
		}
		free(shell->cli);
		shell->cli = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	mode;

	mode = 1;
	if (argc > 2)
		return (write(1, "Error Arg!\n", 10));
	if (argc == 2)
		mode = argv[1][0] - 48;
	return (minishell(mode, envp));
}
