/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:10:49 by stempels          #+#    #+#             */
/*   Updated: 2025/07/03 16:50:01 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**word_splitting(char *str, int len)
{
	char	**argv;
	int	i;
	int	arg_count;
	
	if (!str)
	{
		argv = (char **) malloc(sizeof(char *) * (len + 1));
		if (argv)
			return (NULL);
		argv[len] = NULL;
		return (argv);
	}
	arg_count = 0;
	i = 0;
	while (!match(str[i], IFS))
	{

		i++;
	}
	argv = word_splitting(str + sizeof(char*), len);

}
