/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handl_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:56:10 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 17:59:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handl_env(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '$')
	{
		ft_add_token(tokens, ft_new_token(ENV, "$"));
		*i += 1;
		return (SUCCESS);
	}
	return (FAILURE);
}
