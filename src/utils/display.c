/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/07/15 08:18:14 by stempels         ###   ########.fr       */
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

static char	*build_color_prompt_final(char *fcwd)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin("📁 \033[1;36m", fcwd);
	free(fcwd);
	if (!temp)
		return (ft_strdup("📁 \033[1;36mBlack Hole \033[1;35m$\033[0m "));
	prompt = ft_strjoin(temp, " \033[1;35m$\033[0m ");
	free(temp);
	if (!prompt)
		return (ft_strdup("📁 \033[1;36mBlack Hole \033[1;35m$\033[0m "));
	return (prompt);
}

char	*build_color_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;

	home = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cwd");
		return (ft_strdup("📁 \033[1;36mBlack Hole \033[1;35m$\033[0m "));
	}
	if (home)
		fcwd = ft_strrpl(cwd, home, "~");
	else
		fcwd = ft_strdup(cwd);
	free(cwd);
	if (!fcwd)
		return (ft_strdup("📁 \033[1;36mBlack Hole \033[1;35m$\033[0m "));
	return (build_color_prompt_final(fcwd));
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
		perror("cwd");
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
