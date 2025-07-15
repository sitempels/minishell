/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:31:51 by stempels          #+#    #+#             */
/*   Updated: 2025/07/15 08:03:52 by user             ###   ########.fr       */
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
	parser(shell, &shell->tokens);
	if (!shell->tree)
		return (0);
	execute_node(shell, shell->tree);
	if (g_signal != 0)
		shell->status = 128 + g_signal;
	return (1);
}

int	minishell(t_shell *shell)
{
	while (1)
	{
		if (g_signal != 0)
			shell->status = 128 + g_signal;
		g_signal = 0;
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

int	main(void)
{
	t_shell		*shell;
	extern char	**environ;

	display_banner();
	shell = init_shell(environ);
	if (minishell(shell))
		return (1);
	destroy_shell(shell);
	return (0);
}
