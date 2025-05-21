/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handl_oper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:56:15 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 14:08:39 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handl_pipe(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '|')
	{
		ft_add_token(tokens, ft_new_token(PIPE, "|"));
		*i += 1;
		return (SUCCESS);
	}
	if (cmds[*i] == '|' && cmds[*i + 1] == '|')
	{
		ft_add_token(tokens, ft_new_token(PIPE, "||"));
		*i += 2;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_handl_amper(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '&')
	{
		ft_add_token(tokens, ft_new_token(AMPERSAND, "&"));
		*i += 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_handl_redir(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '<')
	{
		ft_add_token(tokens, ft_new_token(REDIR_IN, "<"));
		*i += 1;
		return (SUCCESS);
	}
	if (cmds[*i] == '<')
	{
		ft_add_token(tokens, ft_new_token(REDIR_OUT, ">"));
		*i += 1;
		return (SUCCESS);
	}
	if (cmds[*i] == '<' && cmds[*i + 1] == '<')
	{
		ft_add_token(tokens, ft_new_token(HEREDOC, "<<"));
		*i += 2;
		return (SUCCESS);
	}
	if (cmds[*i] == '>' && cmds[*i + 1] == '>')
	{
		ft_add_token(tokens, ft_new_token(APPEND, ">>"));
		*i += 2;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_handl_paren(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '(')
	{
		ft_add_token(tokens, ft_new_token(PAREN_LEFT, "("));
		*i += 1;
		return (SUCCESS);
	}
	if (cmds[*i] == ')')
	{
		if (ft_add_token(tokens, ft_new_token(PAREN_RIGHT, ")")))
			*i += 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_handl_oper(t_token **tokens, const char *cmds, int *i)
{
	if (ft_handl_pipe(tokens, cmds, i))
		return (SUCCESS);
	else if (ft_handl_amper(tokens, cmds, i))
		return (SUCCESS);
	else if (ft_handl_redir(tokens, cmds, i))
		return (SUCCESS);
	else if (ft_handl_paren(tokens, cmds, i))
		return (SUCCESS);
	return (FAILURE);
}
