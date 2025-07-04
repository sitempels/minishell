/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 07:36:24 by user              #+#    #+#             */
/*   Updated: 2025/07/04 09:34:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
