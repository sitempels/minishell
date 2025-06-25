/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:31:51 by stempels          #+#    #+#             */
/*   Updated: 2025/06/25 10:26:11 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Implement the new t_shell structure
int	minishell(t_shell *shell)
{
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
			shell->tokens = lexer(shell, &shell->tokens, shell->cli);
			if (!shell->tokens || (shell->tokens)->type == EOL)
				continue ;
			if (shell->mode == 1 || (shell->mode >= 2 && shell->mode != 4))
				show_lexeme(shell->tokens);
			parser(shell, &(shell->tokens));
			if (!shell->tree)
				continue ;
			if (shell->mode == 1 || shell->mode >= 3)
			show_tree(shell->tree, 1);
			if (shell->mode <= 1)
				execute_node(shell, shell->tree, shell->env);
			close(STDOUT_FILENO);
			open(shell->std_io[0], O_RDWR);
			close(STDIN_FILENO);
			open(shell->std_io[1], O_RDWR);
			clean_shell(shell);
		}
	}
	rl_clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	mode;
	t_shell	*shell;

	mode = 1;
	if (argc > 2)
		return (write(1, "Error Arg!\n", 10));
	if (argc == 2)
		mode = argv[1][0] - 48;
	signals();
	display_banner();
	shell = init_shell(mode, envp);
	if (minishell(shell))
		return (1);
	destroy_shell(shell);
	return (0);
}
