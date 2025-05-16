/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:55:00 by stempels          #+#    #+#             */
/*   Updated: 2025/05/16 17:00:23 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_node(t_tokens *tokens)
{
	t_token	*temp;

	temp = tokens;
	(temp->prev)->next = temp->next;
	(temp->next)->prev = temp->prev;
	free(temp);
	return ;
}
