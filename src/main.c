/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:31:51 by stempels          #+#    #+#             */
/*   Updated: 2025/07/23 15:01:55 by stempels         ###   ########.fr       */
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
	{
		write(STDOUT_FILENO, "leaving the shell...\n", 21);
		builtin_exit(shell, 0, NULL);
	}
	signal(SIGQUIT, handle_sigquit);
	if (shell->cli[0] == '\0' || ft_is_all_whitespace(shell->cli))
	{
		free(shell->cli);
		shell->cli = NULL;
		return (0);
	}
	if (is_valid_cli(shell, shell->cli))
		return (0);
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
		restore_std_io(shell);
		clean_shell(shell);
		if (g_signal != 0)
			shell->status = 128 + g_signal;
		g_signal = 0;
		signals();
		if (!read_and_prepare(shell))
			continue ;
		if (!parse_and_execute(shell))
			continue ;
	}
	return (0);
}

int	main(void)
{
	t_shell		*shell;
	extern char	**environ;

	display_banner();
	shell = init_shell(environ);
	minishell(shell);
	destroy_shell(shell);
	return (0);
}
