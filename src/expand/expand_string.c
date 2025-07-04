/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:20:00 by user              #+#    #+#             */
/*   Updated: 2025/07/04 09:35:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_string(const char *input, t_env *env, int exit_status)
{
	size_t	i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] != '$')
			res = append_char(res, input[i++]);
		else
		{
			i++;
			if (input[i] == '?')
			{
				res = expand_exit_code(res, exit_status);
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == '_')
				res = expand_variable(input, &i, env, res);
			else
				res = append_char(res, '$');
		}
	}
	return (res);
}
