/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:25:00 by user              #+#    #+#             */
/*   Updated: 2025/07/03 05:20:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_arg(t_shell *shell, t_token *arg)
{
	char	*raw;
	char	*expanded;

	raw = (char *)ft_calloc(arg->size + 1, sizeof(char));
	if (!raw)
		return (NULL);
	ft_memcpy(raw, arg->start, arg->size);
	free(arg);
	expanded = expand_string(raw, shell->env, shell->status);
	free(raw);
	return (expanded);
}
