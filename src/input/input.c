/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/06/02 16:23:03 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(int mode);
char	*read_line(const char *prompt);
void	ft_display_prompt(void);
static void	display_banner(void);
static void	display_prompt(void);

int	main(int argc, char **argv)
{
	int	mode;

	mode = 1;
	if (argc > 2)
		return (write(1, "Error Arg!\n", 10));
	if (argc == 2)
		mode = argv[1][0] - 48;
	return (minishell(mode));
}

int	minishell(int mode)
{
	char	*line;
	t_token	*token_lst;
	t_node	*tree;

	display_banner();
	while (1)
	{
		token_lst = NULL;
		tree = NULL;
		line = read_line("");
		add_history(line);
		if (!line)
		{
			printf("%sLEAVING the minishell...\n", BOLD_RED);
			exit (0);
		}
		token_lst = lexer(&token_lst, line);
		if (mode == 1 || mode == 2)
			show_lexeme(token_lst);
		if (mode != 2)
		{
			tree = parser(token_lst);
			if (mode == 1 || mode == 3)
				show_tree(tree, 1);
		}
		free(line);
		line = NULL;
	}
	return (0);
}

char	*read_line(const char *prompt)
{
	char	*line;

	display_prompt();
	line = readline(prompt);
	if (!line)
		return (NULL);
	return (line);
}

static void	display_banner(void)
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

static void	display_prompt(void)
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
