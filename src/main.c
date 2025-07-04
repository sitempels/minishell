/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:31:51 by stempels          #+#    #+#             */
/*   Updated: 2025/07/04 22:12:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static int	read_and_prepare(t_shell *shell)
{
	char	*prompt;

	if (g_signal == SIGINT)
	{
		g_signal = 0;
	}
	prompt = build_color_prompt();
	shell->cli = readline(prompt);
	if (!shell->cli)
		ft_error(shell, 1, 1, "leaving the shell...");
	if (!is_valid_cli(shell->cli))
	{
		printf("%sUnclosed quotes%s\n", BOLD_RED, RESET);
		clean_shell(shell);
		return (1);
	}
	add_history(shell->cli);
	return (1);
}

static int	parse_and_execute(t_shell *shell)
{
	shell->tokens = lexer(shell, &shell->tokens, shell->cli);
	if (!shell->tokens || shell->tokens->type == EOL)
		return (0);
	if (shell->mode == 1 || (shell->mode >= 2 && shell->mode != 4))
		show_lexeme(shell->tokens);
	parser(shell, &shell->tokens);
	if (!shell->tree)
		return (0);
	if (shell->mode == 1 || shell->mode >= 3)
		show_tree(shell->tree, 1);
	if (shell->mode <= 1)
		execute_node(shell, shell->tree);
	return (1);
}

static void	wait_and_restore(t_shell *shell)
{
	while (shell->child_nbr > 0)
	{
		wait_and_decrypt_child(shell);
		shell->child_nbr--;
	}
	close(STDOUT_FILENO);
	open(shell->std_io[0], O_RDWR);
	close(STDIN_FILENO);
	open(shell->std_io[1], O_RDWR);
	clean_shell(shell);
}

int	minishell(t_shell *shell)
{
	while (1)
	{
		signals();
		if (!read_and_prepare(shell))
			continue ;
		if (!parse_and_execute(shell))
			continue ;
		wait_and_restore(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		mode;
	t_shell	*shell;

	mode = 0;
	if (argc > 2)
		return (write(1, "Error Arg!\n", 10));
	if (argc == 2)
		mode = argv[1][0] - 48;
	display_banner();
	shell = init_shell(mode, envp);
	if (minishell(shell))
		return (1);
	destroy_shell(shell);
	return (0);
}
