/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handl_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:31:55 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 17:59:21 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handl_sword(t_token **tokens, const char *cmds, int *i, int start)
{
	char	*word;

	while (cmds[*i] && !ft_isspace(cmds[*i]))
	{
		if (ft_isspec(cmds[*i]) || ft_isquote(cmds[*i]))
			break ;
		(*i)++;
	}
	word = ft_strsub(cmds, start, *i - start);
	if (!word)
		return (FAILURE);
	ft_add_token(tokens, ft_new_token(WORD, word));
	free(word);
	return (SUCCESS);
}

int	ft_handl_squote(t_token **tokens, const char *cmds, int *i, int start)
{
	char	*word;

	(*i)++;
	while (cmds[*i] && cmds[*i] != '\'')
		(*i)++;
	if (!cmds[*i])
		return (FAILURE);
	word = ft_strsub(cmds, start + 1, *i - start - 1);
	if (!word)
		return (FAILURE);
	ft_add_token(tokens, ft_new_token(WORD, word));
	free(word);
	(*i)++;
	return (SUCCESS);
}

int	ft_handl_dquote(t_token **tokens, const char *cmds, int *i, int start)
{
	char	*word;

	(*i)++;
	while (cmds[*i] && cmds[*i] != '"')
	{
		if (cmds[*i] == '$')
			ft_handl_env(tokens, cmds, i);
		else
			(*i)++;
	}
	if (!cmds[*i])
		return (FAILURE);
	word = ft_strsub(cmds, start + 1, *i - start - 1);
	if (!word)
		return (FAILURE);
	ft_add_token(tokens, ft_new_token(WORD, word));
	free(word);
	(*i)++;
	return (SUCCESS);
}

int	ft_handl_quote(t_token **tokens, const char *cmds, int *i)
{
	int	start;

	start = *i;
	if (cmds[*i] == '"')
		return (ft_handl_dquote(tokens, cmds, i, start));
	else if (cmds[*i] == '\'')
		return (ft_handl_squote(tokens, cmds, i, start));
	return (FAILURE);
}

int	ft_handl_word(t_token **tokens, const char *cmds, int *i)
{
	int	start;

	start = *i;
	if (ft_isquote(cmds[*i]))
		return (ft_handl_quote(tokens, cmds, i));
	return (ft_handl_sword(tokens, cmds, i, start));
}
