/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 07:36:24 by user              #+#    #+#             */
/*   Updated: 2025/07/08 16:46:41 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *input, size_t *i, t_env *env)
{
	char *key;
	char *val;
	char *res;
	size_t start;
	size_t len;

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
	res = (char *)malloc(len + 1);
	if (!res)
		return (free(input), NULL);
	ft_strlcpy(res, input, start);
	ft_strlcat(res, val, len + 1);
	ft_strlcat(res, &input[*i], len + 1);
	free(input);
	return (res);
}