/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:38:55 by user              #+#    #+#             */
/*   Updated: 2025/06/25 09:04:29 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Only display the variable exported with non NULL value
int	builtin_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
	{
		printf("No environment variables set.\n");
		return (1);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
