/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/06/23 09:23:26 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Implement the new t_shell structure
int	minishell(int mode, char **env)
{
	int	status;
	pid_t	subshell;
	t_shell	*shell;

	signals();
	display_banner();
	shell = init_shell(mode, env);
	while (1)
	{
		display_prompt();
		shell->cli = readline("\033[1;32m$\033[0m ");
		if (!shell->cli)
		{
			printf("%sLEAVING the minishell...\n", BOLD_RED);
			break ;
		}
		if (!is_valid_cli(shell->cli))
		{
			printf("%sUnclosed quotes%s\n", BOLD_RED, RESET);
			free(shell->cli);
			shell->cli = NULL;
		}
		else
		{
			add_history(shell->cli);
			subshell = fork();
			if (subshell < 0)
				ft_error(shell, 1, "MINISHELL CRASHED !!!!!");
			if (subshell == 0)
			{
				shell->tokens = lexer(shell, &shell->tokens, shell->cli);
				if (shell->mode == 1 || (shell->mode >= 2 && shell->mode != 4))
					show_lexeme(shell->tokens);
				shell->tree = parser(shell, &(shell->tokens));
				if (!shell->tree)
					return (1);
				if (shell->mode == 1 || shell->mode >= 3)
				show_tree(shell->tree, 1);
				if (shell->mode <= 1)
				{
					execute_node(shell, shell->tree, envp_from_env(shell->env));
					return (0);
				}
			}
			waitpid(subshell, &status, 0);
			clean_shell(shell);
		}
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
