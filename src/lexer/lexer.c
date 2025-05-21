/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 10:47:25 by stempels          #+#    #+#             */
/*   Updated: 2025/05/21 17:09:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match(char c, char *match_lst);
static int	assign_type(char *token, int *pos);
static int	new_token(t_token **token_lst, char *token, int *pos);
int			token_addback(t_token **tokens, t_token *token);
t_token		*last_token(t_token **tokens);

t_token	**lexer(char *cl)
{
	int		i;
	int		j;
	t_token	**token_lst;

	i = 0;
	while (cl[i])
	{
		j = 0;
		while (cl[i + j])
		{
			if (cl[i + j + 1] && match(cl[i + j + 1], DELIMITERS))
				if (!new_token(token_lst, &cl[i], &j))
					return (NULL);
			j++;
		}
		i = i + j;
		i++;
	}
	return (token_lst);
}

static int	match(char c, char *match_lst)
{
	int	i;

	i = 0;
	while (match_lst[i])
		if (match_lst[i] == c)
			return (1);
	return (0);
}

static int	new_token(t_token **token_lst, char *token, int *pos)
{
	t_token	*new;

	new = (t_token *) ft_calloc(1, sizeof(t_token));
	if (!new)
		return (0);
	new->type = assign_type(token, pos);
	new->start = token;
	(*pos)++;
	new->size = *pos;
	token_addback(token_lst, new);
//	if (token[j + 1] && match(token[j + 1], OPERATOR))
//		if (!new_token(token_list, token[j + 1], 0))
//			return (0);
	return (1);
}

static int	assign_type(char *token, int *pos)
{
	if (token[*pos] == '\0')
		return (EOL);
	if (token[*pos] == '|' && token[*pos + 1] == '|')
		return ((*pos)++, OR_IF);
	if (token[*pos] == '|')
		return (OR);
	if (token[*pos] == '&' && token[*pos + 1] == '&')
		return ((*pos++), AND_IF);
	if (token[*pos] == '<' && token[*pos + 1] == '<')
		return ((*pos)++, DLESS);
	if (token[*pos] == '<')
		return (LESS);
	if (token[*pos] == '>' && token[*pos + 1] == '>')
		return ((*pos)++, DGREAT);
	if (token[*pos] == '>')
		return (GREAT);
	if (token[*pos] == '\n')
		return (NEWLINE);
	else
		return (WORD);
}

t_token	*last_token(t_token **tokens)
{
	t_token	*last;

	if (!tokens || !*tokens)
		return (NULL);
	last = *tokens;
	while (last->next)
		last = last->next;
	return (last);
}

int	token_addback(t_token **tokens, t_token *token)
{
	t_token	*last;

	if (!token)
		return (FAILURE);
	if (!*tokens)
	{
		*tokens = token;
		return (SUCCESS);
	}
	last = last_token(tokens);
	last->next = token;
	return (SUCCESS);
}

int	main(void)
{
	char *line;
	int	j;
	t_token	**token_lst;
	t_token	*temp;

	line = "ls ls ls ls";
	token_lst = lexer(line);
	temp = *token_lst;	
	while (temp)
	{
		printf("TOKEN_TYPE: %d	",temp->type);
		printf("TOKEN_CONTENT: ");
		j = 0;
		while (j < temp->size)
		{
			write(1, &(temp->start[j]), 1);
			j++;
		}
		temp = temp->next;
	}
}
