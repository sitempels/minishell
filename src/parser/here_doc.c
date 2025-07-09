/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:46 by stempels          #+#    #+#             */
/*   Updated: 2025/07/09 14:41:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc(t_shell *shell, char *here_doc);
static int	write_heredoc(t_shell *shell, t_token del, int fd, int quoted);
static int	heredoc_cmp(char *line, char *del, size_t len);

t_node	*handle_heredoc(t_shell *shell, t_node *del)
{
	int		fd;
	int		quoted;
	char	*here_name;

	here_name = create_heredoc(shell, ".here_doc/heredoc");
	fd = open(here_name, O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
	{
		shell->status = 1;
		free(here_name);
		ft_error(shell, 0, 2, "HERE_DOC", get_errnum(OPEN_FILE));
	}
	is_quoted(del->use.content, &quoted);
	while (g_signal != SIGINT
		&& write_heredoc(shell, *(del->use.content), fd, quoted))
		continue ;
	//unlink(here_name);
	free(here_name);
	del->use.fd = fd;
	if (g_signal == SIGINT)
		return (free(del), NULL);
	//if (-close(fd))
	//	ft_error(shell, 0, 2, "HERE_DOC", get_errnum(CLOSE_FILE));
	return (del);
}

static char	*create_heredoc(t_shell *shell, char *here_doc)
{
	int		nbr;
	int		found;
	char	*str_nbr;
	char	*here_name;

	nbr = 0;
	found = 0;
	while (found >= 0 && nbr < MAX_HEREDOC)
	{
		str_nbr = ft_itoa(nbr);
		here_name = ft_strjoin(here_doc, str_nbr);
		free(str_nbr);
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

static int	write_heredoc(t_shell *shell, t_token del, int fd, int quoted)
{
	int		i;
	char	*line;
	char	**line_arr;

	signal(SIGINT, handle_here_doc);
	line = readline("heredoc>> ");
	if (!line)
		return (0);
	if (!heredoc_cmp(line, del.start, del.size) || g_signal == SIGINT)
		return (free(line), 0);
	if (!quoted)
	{
		line_arr = expand(shell, NULL, line);
		i = -1;
		while (line_arr[++i])
		{
			write(fd, line_arr[i], ft_strlen(line_arr[i]));
			free(line_arr[i]);
		}
		free(line_arr);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

static int	heredoc_cmp(char *line, char *del, size_t len)
{
	size_t	i;
	size_t	j;	

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (del[i + j] && (del[i + j] == '\'' || del[i + j] == '\"'))
		{
			j = j + 1;
			continue ;
		}
		if (!line[i] || line[i] != del[i + j])
			return (1);
		i++;
	}
	if (!line[i] && i + j == len)
		return (0);
	return (1);
}
