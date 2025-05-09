/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:33 by stempels          #+#    #+#             */
/*   Updated: 2025/05/09 11:54:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef	enum	s_token_type
{
	ERROR;
	WORD;
	OPERATOR_FLOW;
	OPERATOR_RED;
}		t_token_type;

typedef struct	s_token
{
	t_token_type	token_type;
	char		*start;
	size_t		size;
	t_token		*next;
}	t_token;
#endif
