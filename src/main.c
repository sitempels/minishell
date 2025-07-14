/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:31:51 by stempels          #+#    #+#             */
/*   Updated: 2025/07/14 19:11:03 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	ft_is_all_whitespace(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static int	read_and_prepare(t_shell *shell)
{
	char	*prompt;

	if (g_signal == SIGINT)
		g_signal = 0;
	prompt = build_color_prompt();
	shell->cli = readline(prompt);
	free(prompt);
	if (!shell->cli)
		ft_error(shell, 1, 1, "leaving the shell...");
	signal(SIGQUIT, handle_sigquit);
	if (shell->cli[0] == '\0' || ft_is_all_whitespace(shell->cli))
	{
		free(shell->cli);
		shell->cli = NULL;
		return (0);
	}
	if (!is_valid_cli(shell->cli))
	{
		printf("%sUnclosed quotes%s\n", BOLD_RED, RESET);
		clean_shell(shell);
		return (0);
	}
	if (shell->cli && *shell->cli)
		add_history(shell->cli);
	return (1);
}

static int	parse_and_execute(t_shell *shell)
{
	if (!shell->cli)
		return (0);
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

int	minishell(t_shell *shell)
{
	while (1)
	{
		signals();
		if (!read_and_prepare(shell))
			continue ;
		if (!parse_and_execute(shell))
			continue ;
		restore_std_io(shell);
		clean_shell(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		mode;
	t_shell	*shell;

	mode = 0;
	if (argc > 2)
		return (write(1, "Usage: ./minishell <mode>\n", 10));
	if (argc == 2)
		mode = argv[1][0] - 48;
	display_banner();
	shell = init_shell(mode, envp);
	if (minishell(shell))
		return (1);
	destroy_shell(shell);
	return (0);
}
