/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:15:51 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 17:52:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*ft_typestr(t_type type)
{
	if (type == VOID)
		return ("VOID");
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == AMPERSAND)
		return ("AMPERSAND");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == PAREN_LEFT)
		return ("PAREN_LEFT");
	if (type == PAREN_RIGHT)
		return ("PAREN_RIGHT");
	if (type == WILDCARD)
		return ("WILDCARD");
	if (type == ENV)
		return ("ENV");
	return ("UNKNOWN");
}

void	ft_print_tokens(t_token **tokens)
{
	int	i;

	if (!tokens || !*tokens)
	{
		printf("{\n  \"tokens\": []\n}\n");
		return ;
	}
	i = 1;
	printf("{\n   \"tokens\": [\n");
	while (*tokens)
	{
		printf("   {\n");
		printf("      \"index\": %d,\n", i);
		printf("      \"type\": \"%s\",\n", ft_typestr((*tokens)->type));
		printf("      \"value\": \"%s\"\n", (*tokens)->token);
		printf("   }");
		tokens = &(*tokens)->next;
		if (*tokens)
			printf(",\n");
		else
			printf("\n");
		i++;
	}
	printf("  ]\n}\n");
}

static const char	*ft_lvlcolor(t_level level)
{
	if (level == DEBUG)
		return (CYAN);
	if (level == INFO)
		return (GREEN);
	if (level == WARN)
		return (YELLOW);
	if (level == ERROR)
		return (RED);
	return (RESET);
}

static const char	*ft_lvlstr(t_level level)
{
	if (level == DEBUG)
		return ("DEBUG");
	if (level == INFO)
		return ("INFO");
	if (level == WARN)
		return ("WARN");
	if (level == ERROR)
		return ("ERROR");
	return ("UNKNOWN");
}

void	ft_logdebug(t_level level, const char *log)
{
	printf("[%s%s%s] - %d - %s - \"%s\"%s\n", ft_lvlcolor(level),
		ft_lvlstr(level), RESET, errno, strerror(errno), log, RESET);
}
