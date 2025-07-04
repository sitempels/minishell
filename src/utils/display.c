/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/07/04 16:17:41 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_banner(void)
{
	const char	*b;

	b = "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		"Build by Simon T. && Selim J.\n";
	printf(MAGENTA);
	printf("\n\n");
	printf("%s", b);
	printf("\n\n");
	printf(RESET);
}

void	display_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;
	char	*tty;
	int		ttys;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd CD RM DIR ERROR");
		cwd = ft_strdup("<unknown>");
		if (!cwd)
			return ;
	}
	fcwd = ft_strrpl(cwd, home, "~");
	if (!fcwd)
	{
		fcwd = ft_strdup(cwd);
		if (!fcwd)
		{
			free(cwd);
			return ;
		}
	}
	tty = ttyname(STDIN_FILENO);
	printf("📁 %s%s 💻 %s", BOLD_CYAN, fcwd, BOLD_MAGENTA);
	ttys = ttyslot();
	if (tty)
		printf("%s", tty);
	printf(" 🎰 %s%d%s\n ", BOLD_YELLOW, ttys, RESET);
	free(cwd);
	free(fcwd);
}
