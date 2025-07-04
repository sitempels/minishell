/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/07/04 21:28:11 by user             ###   ########.fr       */
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

// void	display_prompt(void)
// {
// 	char	*home;
// 	char	*cwd;
// 	char	*fcwd;
// 	char	*tty;
// 	int		ttys;

// 	home = getenv("HOME");
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		perror("getcwd CD RM DIR ERROR");
// 		cwd = ft_strdup("<unknown>");
// 		if (!cwd)
// 			return ;
// 	}
// 	fcwd = ft_strrpl(cwd, home, "~");
// 	if (!fcwd)
// 	{
// 		fcwd = ft_strdup(cwd);
// 		if (!fcwd)
// 		{
// 			free(cwd);
// 			return ;
// 		}
// 	}
// 	printf("📁 %s%s 💻 %s", BOLD_CYAN, fcwd, BOLD_MAGENTA);
// 	free(cwd);
// 	free(fcwd);
// }

char	*build_color_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;
	char	*prompt;
	char	*temp;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (ft_strdup("📁 <unknown> \033[1;35m$\033[0m "));
	}
	fcwd = ft_strrpl(cwd, home, "~");
	if (!fcwd)
		fcwd = ft_strdup(cwd);
	free(cwd);
	if (!fcwd)
		return (ft_strdup("📁 <unknown> \033[1;35m$\033[0m "));
	temp = ft_strjoin("📁 \033[1;36m", fcwd);
	free(fcwd);
	if (!temp)
		return (ft_strdup("📁 <unknown> \033[1;35m$\033[0m "));
	prompt = ft_strjoin(temp, " \033[1;35m$\033[0m ");
	return (free(temp), prompt);
}

char	*build_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;
	char	*prompt;
	char	*temp;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (ft_strdup("<unknown> $ "));
	}
	fcwd = ft_strrpl(cwd, home, "~");
	if (!fcwd)
		fcwd = ft_strdup(cwd);
	free(cwd);
	if (!fcwd)
		return (ft_strdup("<unknown> $ "));
	temp = ft_strjoin("", fcwd);
	free(fcwd);
	if (!temp)
		return (ft_strdup("<unknown> $ "));
	prompt = ft_strjoin(temp, " $ ");
	return (free(temp), prompt);
}
