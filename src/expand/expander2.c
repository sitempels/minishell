/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:59:43 by stempels          #+#    #+#             */
/*   Updated: 2025/06/20 12:29:39 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_arg(t_shell *shell, t_token *arg)
{
	char	**argv;

	if (!arg)
	{
		
	}
}

int	expand_param(t_shell *shell, t_token *token)
{
	int	size;
	t_env	*var;

	size = 0;
	while (size < token->size)
	{
		if (token->start[size] == $)
			var = get_env_var(token->start, &size);
		size++;
	}

}

void	word_splitting(t_shell *shell, t_token *token, char **arg)
{
	int	i;

	while (i < token->size)
}
