/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:15:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:20:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_code(char *res, int exit_status)
{
	char	*code;

	code = ft_itoa(exit_status);
	if (!code)
		return (res);
	res = append_str(res, code);
	free(code);
	return (res);
}

char	*expand_variable(const char *input, size_t *i, t_env *env, char *res)
{
	char	*key;
	char	*val;
	size_t	start;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_strsub(input, start, *i - start);
	if (!key)
		return (res);
	val = get_env_value(env, key);
	free(key);
	if (val)
		res = append_str(res, ft_strdup(val));
	return (res);
}
