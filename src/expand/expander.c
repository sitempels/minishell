/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:18:04 by stempels          #+#    #+#             */
/*   Updated: 2025/06/11 10:46:42 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TO DO: .Brace expansion --> NOT NEEDED?
	 .Tilde expansion --> NOT NEEDED?
	 .Shell Parameter expansionn --> $ handled here
	 .Command Substitutionn --> NOT NEEDED?
	 .Arithmetic expansionn --> NOT NEEDED?
	 .Process Substitutionn --> NOT NEEDED?
	 .Word splitting --> split function IFS( \t\n)
	 .Filename expansion --> * handled here
	 .Quote removal --> remove '' || ""
*/

void	*expander(t_token *token)
{
	int		i;
	int		size;
	char	*start;
	char	*new;

	if (token->type == EOL)
		return (NULL);
	start = (token->start);
	size = token->size;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	i = 0;
	while (i < size)
	{
		new[i] = start[i];
		i++;
	}
	return ((void *)new);
}

int	calc_expand(t_token *arg)
{
	int	i;
	char	quote;

	i = 0;
	while (i < (int)(arg->size))
	{
		if (arg->start[i] == '\'' || arg->start[i] == '\"')
		{
			quote = arg->start[i];
			i++;
			while (arg->start[i] != quote)
				i++;
		}
		i++;
	}
}
