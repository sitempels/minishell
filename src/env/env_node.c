/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 05:20:00 by user              #+#    #+#             */
/*   Updated: 2025/07/10 17:03:30 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *env)
{
	size_t	len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, len + 1);
	return (key);
}

char	*extract_value(char *env)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
		return (NULL);
	return (ft_strdup(equal_sign + 1));
}

// char	*extract_value(char *str)
// {
// 	char	*equal_sign;
// 	char	*raw_value;
// 	char	*clean_value;
// 	size_t	len;

// 	if (!str)
// 		return (NULL);
// 	equal_sign = ft_strchr(str, '=');
// 	if (!equal_sign || !equal_sign[1])
// 		return (ft_strdup(""));
// 	raw_value = ft_strdup(equal_sign + 1);
// 	if (!raw_value)
// 		return (NULL);
// 	len = ft_strlen(raw_value);
// 	if (len >= 2 && ((raw_value[0] == '"' && raw_value[len - 1] == '"')
// 			|| (raw_value[0] == '\'' && raw_value[len - 1] == '\'')))
// 	{
// 		clean_value = ft_strsub(raw_value, 1, len - 2);
// 		free(raw_value);
// 		return (clean_value);
// 	}
// 	return (raw_value);
// }

t_env	*new_env(char *env)
{
	t_env	*new;
	char	*key;
	char	*value;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	key = extract_key(env);
	if (!key)
		return (free(new), NULL);
	if (ft_strchr(env, '='))
	{
		value = extract_value(env);
		if (!value)
			return (free(key), free(new), NULL);
	}
	else
		value = NULL;
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_freeone(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}
