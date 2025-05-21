/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:39:19 by sjacquet          #+#    #+#             */
/*   Updated: 2025/05/11 15:59:07 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenize_cmds(const char *cmds)
{
	int		i;
	t_token	*tokens;

	if (!cmds)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (cmds[i])
	{
		if (ft_isspace(cmds[i]))
		{
			i++;
			continue ;
		}
		if (ft_handl_word(&tokens, cmds, &i))
			continue ;
		if (ft_handl_oper(&tokens, cmds, &i))
			continue ;
		if (ft_handl_wild(&tokens, cmds, &i))
			continue ;
		i++;
	}
	return (tokens);
}
