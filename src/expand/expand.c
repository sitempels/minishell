/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 06:30:00 by user              #+#    #+#             */
/*   Updated: 2025/07/07 15:22:48 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_arg_token(t_shell *shell, t_token *arg, int nbr);
static char	**get_arg_array(t_shell *shell, char *start);

char	**expand(t_shell *shell, t_token *arg, char *str)
{
	char	**argv;

	if (arg)
		argv = get_arg_token(shell, arg, 0);
	if (str)
		argv = get_arg_array(shell, str);
	argv = word_splitting(argv, 0, 0);
	argv = quote_removal(argv);
	return (argv);
}

static char	**get_arg_token(t_shell *shell, t_token *arg, int nbr)
{
	char	**argv;

	if (!arg)
	{
		argv = (char **)ft_calloc(nbr + 1, sizeof(char *));
		if (!argv)
			return (NULL);
		return (argv);
	}
	argv = get_arg_token(shell, arg->next, nbr + 1);
	if (!argv)
		return (free(arg), NULL);
	argv[nbr] = process_arg(shell, arg->start, arg->size);
	if (!argv[nbr])
		return (free(arg), NULL);
	return (argv);
}

static char	**get_arg_array(t_shell *shell, char *arg)
{
	char	**argv;

	argv = (char **) malloc(sizeof(char *) * (2));
	if (!argv)
		return (NULL);
	argv[1] = NULL;
	argv[0] = process_arg(shell, arg, ft_strlen(arg));
	free(arg);
	return (argv);
}
