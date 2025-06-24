/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:46 by stempels          #+#    #+#             */
/*   Updated: 2025/06/24 15:29:40 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc(t_shell *shell, char *here_doc);
static	int	heredoc_cmp(char *line, char *end, size_t len, int *quoted);

t_token	*handle_heredoc(t_shell *shell, t_token *end)
{
	int		fd;
	int		quoted;
	char	*line;
	char	*here_name;

	here_name = create_heredoc(shell, ".here_doc/heredoc");
	fd = open(here_name, O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
		ft_error(shell, 2, "HERE_DOC", get_errnum(OPEN_FILE));
	while (1)
	{
		line = readline(">");
		if (!line || !heredoc_cmp(line, end->start, end->size, &quoted))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	end->start = here_name;
	end->size = ft_strlen(here_name);
	if (-close(fd))
		ft_error(shell, 2, "HERE_DOC", get_errnum(CLOSE_FILE));
	return (end);
}

static char	*create_heredoc(t_shell *shell, char *here_doc)
{
	int		nbr;
	int		found;
	char	*here_name;

	nbr = 0;
	found = 0;
	while (found >= 0 && nbr < MAX_HEREDOC)
	{
		here_name = ft_strjoin(here_doc, ft_itoa(nbr));
		if (!here_name)
			ft_error(shell, 2, "HERE_DOC", get_errnum(CREAT_FILE));
		found = access(here_name, F_OK);
		if (found == -1)
			return (here_name);
		nbr++;
		free(here_name);
	}
	ft_error(shell, 1, "HERE_DOC: Maximum here_doc reached");
	return (NULL);
}

static	int	heredoc_cmp(char *line, char *end, size_t len, int *quoted)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*quoted = 0;
	while ((line[i + j] || end[i + *quoted]) && i + *quoted < len)
	{
		//if (end[i + *quoted] == '\\')
		//{
		if (end[i + *quoted] && (end[i + *quoted] == '\'' ||
			end[i + *quoted] == '\"'))
			*quoted = *quoted + 1;
//		if (line[i + j] == '\\')
//		{
		if (line[i + j] && (line[i + j] == '\'' ||
			line[i + j] == '\"'))
			j = j + 1;
//		}
		if (line[i + j] != end[i + *quoted])
			return (1);
		i++;
	}
	return (0);
}
