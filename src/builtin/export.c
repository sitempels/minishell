/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:34 by user              #+#    #+#             */
/*   Updated: 2025/06/09 21:42:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_env **head, t_env *new)
{
	t_env *last;

	if (!new)
		return (1);
	if (!*head)
	{
		*head = new;
		return (0);
	}
	last = env_getlast(*head);
	last->next = new;
	return (0);
}