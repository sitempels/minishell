/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/06/09 02:58:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(const char *prompt)
{
	char	*line;

	display_prompt();
	line = readline(prompt);
	if (!line)
		return (NULL);
	return (line);
}

int	minishell(int mode, char **env)
{
	char	*line;
	t_token	*token_lst;
	t_node	*tree;

	signals();
	display_banner();
	while (1)
	{
		token_lst = NULL;
		tree = NULL;
		line = read_line("\033[1;32m$\033[0m ");
		add_history(line);
		if (!line)
		{
			printf("%sLEAVING the minishell...\n", BOLD_RED);
			exit(0);
		}
		token_lst = lexer(&token_lst, line);
		if (!token_lst)
			return (1);
		if (mode == 1 || (mode >= 2 && mode != 4))
			show_lexeme(token_lst);
		tree = parser(token_lst);
		if (!tree)
			return (1);
		if (mode == 1 || mode >= 3)
			show_tree(tree, 1);
		if (mode <= 1)
			execute(tree, env);
		free(line);
		line = NULL;
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
