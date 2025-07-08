/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:20:00 by user              #+#    #+#             */
/*   Updated: 2025/07/08 17:47:04 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(t_shell *shell, char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] && input[i] == '&' && input[i + 1] == '\'')
		{
			i += 2;
			while (!(input[i] == '&' && input[i + 1] == '\''))
				i++;
			i += 2;
		}
		else if (input[i] && input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				input = expand_exit_code(input, i, shell->status);
				if (!input)
					return (NULL);
				i += 2;
			}
			else if (ft_isalpha(input[i + 1]) || input[i + 1] == '_')
			{
				i++;
				input = expand_variable(input, &i, shell->env);
				if (!input)
					return (NULL);
			}
			else if (input[i + 1] == '$')
				i += 2;
			else
				i++;
			continue ;
		}
		i++;
	}
	return (input);
}
