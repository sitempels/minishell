/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:46:33 by stempels          #+#    #+#             */
/*   Updated: 2025/05/18 07:38:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stddef>

typedef enum s_token_type
{
	ERROR,
	WORD,
	OPERATOR_FLOW,
	OPERATOR_RED,
}					t_token_type;

typedef struct s_token
{
	t_token_type	token_type;
	char			*start;
	size_t			size;
	t_token			*next;
}					t_token;
#endif
