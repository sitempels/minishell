/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:47:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/18 06:28:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *cl)
{
	int		i;
	int		j;
	t_token	*token_lst;

	/*if(verif)
		*/
	i = 0;
	while (cl[i])
	{
		j = 0;
		while (cl[i + j])
		{
			token_addback(token_lst, token_new(match(cl[i + j])));
			if (!token_lst)
				return (/*ERROR*/);
			j++;
		}
		token_lst->size = j;
		i = i + j;
		i++;
	}
	return (token_lst);
}
