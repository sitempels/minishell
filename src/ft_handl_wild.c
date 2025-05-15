/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handl_wild.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:56:13 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 14:08:49 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handl_wild(t_token **tokens, const char *cmds, int *i)
{
	if (cmds[*i] == '*')
	{
		ft_add_token(tokens, ft_new_token(WILDCARD, "*"));
		*i += 1;
		return (SUCCESS);
	}
	return (FAILURE);
}
