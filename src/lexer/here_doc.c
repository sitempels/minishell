/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:46 by stempels          #+#    #+#             */
/*   Updated: 2025/07/04 17:47:59 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc(t_shell *shell, char *here_doc);
static void	is_quoted(t_token *end, int *quoted);
static int	heredoc_cmp(char *line, char *end, size_t len);

t_token	*handle_heredoc(t_shell *shell, t_token *end)
{
	int		i;
	int		fd;
	int		quoted;
	char	*line;
	char	**line_arr;
	char	*here_name;

	here_name = create_heredoc(shell, ".here_doc/heredoc");
	fd = open(here_name, O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
		ft_error(shell, 0, 2, "HERE_DOC", get_errnum(OPEN_FILE));
	is_quoted(end, &quoted);
	while (1)
	{
		signal(SIGINT, handle_here_doc);
		line = readline("heredoc>> ");
		if (!line || !heredoc_cmp(line, end->start, end->size))
			break ;
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(line);
			return (NULL);
		}
		i = 0;
		if (!quoted)
		{
			while (line_arr[i])
			{
				line_arr = expand(shell, NULL, line);
				write(fd, line_arr[i], ft_strlen(line_arr[i]));
				i++;
			}
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	end->start = here_name;
	end->size = ft_strlen(here_name);
	if (-close(fd))
		ft_error(shell, 0, 2, "HERE_DOC", get_errnum(CLOSE_FILE));
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
			ft_error(shell, 0, 2, "HERE_DOC", get_errnum(CREAT_FILE));
		found = access(here_name, F_OK);
		if (found == -1)
			return (here_name);
		nbr++;
		free(here_name);
	}
	ft_error(shell, 0, 1, "HERE_DOC: Maximum here_doc reached");
	return (NULL);
}

static int	heredoc_cmp(char *line, char *end, size_t len)
{
	size_t	i;
	size_t	j;	

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (end[i + j] && (end[i + j] == '\'' || end[i
				+ j] == '\"'))
		{
			j = j + 1;
			continue ;
		}
		if (!line[i] || line[i] != end[i + j])
			return (1);
		i++;
	}
	if (!line[i] && i + j == len)
		return (0);
	return (1);
}

static void	is_quoted(t_token *end, int *quoted)
{
	size_t	i;

	i = 0;
	*quoted = 0;
	while (i < end->size)
	{
		if (end->start[i] == '\'' || end->start[i] == '\"')
			(*quoted)++;
		i++;
	}
}
