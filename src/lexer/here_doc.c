/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:46 by stempels          #+#    #+#             */
/*   Updated: 2025/06/12 15:36:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc(char *here_doc);

t_token	*handle_heredoc(t_token *end)
{
	int		fd;
	char	*line;
	char	*here_name;

	here_name = create_heredoc("here_doc/heredoc");
	fd = open(here_name, O_WRONLY | O_CREAT, 00644);
	while (1)
	{
		line = readline(">");
		if (!line)
			return (NULL);
		if (!strncmp(line, end->start, end->size))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	end->start = here_name;
	end->size = ft_strlen(here_name);
	close(fd);
	return (end);
}

static char	*create_heredoc(char *here_doc)
{
	int		nbr;
	int		found;
	char	*here_name;

	nbr = 0;
	found = 0;
	while (found >= 0 && nbr < MAX_HEREDOC)
	{
		here_name = ft_strjoin(here_doc, ft_itoa(nbr));
		found = access(here_name, F_OK);
		if (found == -1)
			return (here_name);
		nbr++;
	}
	return (NULL);
}
