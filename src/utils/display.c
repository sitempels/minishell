/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:56:41 by stempels          #+#    #+#             */
/*   Updated: 2025/07/15 08:46:49 by user             ###   ########.fr       */
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

char	*format_cwd_with_home(char *cwd, char *home)
{
	size_t	home_len;
	char	*fcwd;

	if (!home || !cwd)
	{
		if (cwd)
			return (ft_strdup(cwd));
		else
			return (ft_strdup("<deleted>"));
	}
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0 && (cwd[home_len] == '/'
			|| cwd[home_len] == '\0'))
	{
		fcwd = ft_strrpl(cwd, home, "~");
	}
	else
	{
		fcwd = ft_strdup(cwd);
	}
	return (fcwd);
}

char	*build_prompt_str(char *path)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin("📁 \033[1;36m", path);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin(temp, " \033[1;35m$\033[0m ");
	free(temp);
	return (prompt);
}

char	*build_color_prompt(void)
{
	char	*home;
	char	*cwd;
	char	*fcwd;
	char	*prompt;

	home = getenv("HOME");
	cwd = get_safe_cwd();
	if (!cwd)
		return (ft_strdup("📁 \033[1;31m<deleted>\033[0m \033[1;35m$\033[0m "));
	fcwd = format_cwd_with_home(cwd, home);
	free(cwd);
	if (!fcwd)
		return (ft_strdup("📁 \033[1;31m<deleted>\033[0m \033[1;35m$\033[0m "));
	prompt = build_prompt_str(fcwd);
	free(fcwd);
	if (!prompt)
		return (ft_strdup("📁 \033[1;31m<deleted>\033[0m \033[1;35m$\033[0m "));
	return (prompt);
}
