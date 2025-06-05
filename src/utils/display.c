/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
<<<<<<< HEAD:src/input/input.c
/*   Updated: 2025/06/05 16:31:59 by stempels         ###   ########.fr       */
=======
/*   Updated: 2025/06/05 16:43:07 by sjacquet         ###   ########.fr       */
>>>>>>> origin/work:src/utils/display.c
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
		"Buidl by Simon T. && Selim J.\n";
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
	fcwd = ft_strrpl(cwd, home, "~");
	tty = ttyname(STDIN_FILENO);
	ttys = ttyslot();
	printf("📁 %s%s 💻 %s%s 🎰 %s%d%s\n ", BOLD_CYAN, fcwd, BOLD_MAGENTA, tty,
		BOLD_YELLOW, ttys, RESET);
	free(cwd);
	free(fcwd);
}
