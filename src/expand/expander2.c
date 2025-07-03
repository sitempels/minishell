/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:59:43 by stempels          #+#    #+#             */
/*   Updated: 2025/07/03 05:18:52 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_new_size(t_shell *shell, t_token *arg, size_t i, int *quoted)
{
	t_env	*tmp;
	size_t	len;

	if (i == arg->size)
		return (0);
	len = i;
	if (arg->start[i] == '?')
		len = ft_intlen_base(shell->status, BASE_10);
	else if (ft_isalpha(arg->start[i]) || arg->start[i] == '_')
	{
		while (!match(arg->size[i], DELIMITERS))
			i++;
		tmp = env_getone(shell->env, arg->start[len], i - len);
		if (!tmp)
			return (0);
		len = ft_strlen(tmp->value)
	}
	len += get_new_size(shell, arg, i, *quoted);
	return (len);
}

char	*expand_arg(t_shell *shell, t_token *arg, t_env *env, int status,
		int *quoted)
{
	size_t	len;
	size_t	i;
	char	*var;

	len = 0;
	i = 0;
	while (i < arg->size)
	{
		if (arg->start[i] == '\'' || arg->size[i] == '\"')
		{
			*quoted = 1;
			i++;
		}
		if (arg->start[i] == '$')
		{
			i++;
			len += get_new_size(shell, arg, i, *quoted);
		}
	}
}
