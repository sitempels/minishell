/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 07:36:24 by user              #+#    #+#             */
/*   Updated: 2025/07/15 07:06:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *input, size_t *i, t_env *env)
{
	char	*key;
	char	*val;
	char	*res;
	size_t	start;
	size_t	len;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	key = ft_strsub(input, start, *i - start);
	if (!key)
		return (input);
	val = get_env_value(env, key);
	free(key);
	if (!val)
		val = "";
	len = ft_strlen(input) - (*i - start) + ft_strlen(val);
	res = (char *)malloc(len);
	if (!res)
		return (free(input), NULL);
	res[len] = '\0';
	ft_strlcpy(res, input, start);
	ft_strlcat(res, val, len);
	ft_strlcat(res, &input[*i], len);
	return (free(input), res);
}
