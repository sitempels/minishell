/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/06/10 02:57:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(int mode, char **env)
{
	pid_t	pid;
	char	*line;
	t_token	*token_lst;
	t_node	*tree;

	signals();
	display_banner();
	while (1)
	{
		token_lst = NULL;
		tree = NULL;
		display_prompt();
		line = readline("\033[1;32m$\033[0m ");
		if (!line)
		{
			printf("%sLEAVING the minishell...\n", BOLD_RED);
			break ;
		}
		add_history(line);
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
		{
			pid = fork();
			if (pid < 0)
				return (1);
			else if (pid == 0)
				execute(tree, env);
			else
				wait(&pid);
		}
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
