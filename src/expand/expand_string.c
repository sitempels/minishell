/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:20:00 by user              #+#    #+#             */
/*   Updated: 2025/07/15 16:51:56 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_and_quote_block(char *input, size_t i)
{
	if (input[i] == '&' && input[i + 1] == '\'')
	{
		i += 2;
		while (input[i] && !(input[i] == '&' && input[i + 1] == '\''))
			i++;
		if (input[i])
			i++;
	}
	return (i);
}

static char	*expand_exit_dollar(char *input, size_t i, t_shell *shell)
{
	input = expand_exit_code(input, i, shell->status);
	if (!input)
		return (NULL);
	return (input);
}

static char	*expand_named_variable(char *input, size_t *i, t_shell *shell)
{
	(*i)++;
	input = expand_variable(input, i, shell->env);
	if (!input)
		return (NULL);
	return (input);
}

char	*expand_string(t_shell *shell, char *input)
{
	size_t	i;

	if (!input)
		return (NULL);
	i = 0;
	while (input[i])
	{
		i = skip_and_quote_block(input, i);
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				input = expand_exit_dollar(input, i, shell);
			else if (ft_isalpha(input[i + 1]) || input[i + 1] == '_')
				input = expand_named_variable(input, &i, shell);
			else
				i++;
			if (!input)
				return (NULL);
		}
		i++;
	}
	return (input);
}
