/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:38:46 by stempels          #+#    #+#             */
/*   Updated: 2025/08/04 15:39:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc(t_shell *shell, char *here_doc);
static int	write_heredoc(t_shell *shell, t_token del, int fd, int quoted);
static void	expand_and_write(t_shell *shell, char *line, int fd);
static int	heredoc_cmp(char *line, char *del, size_t len);

t_node	*handle_heredoc(t_shell *shell, t_node *del)
{
	int		fd;
	int		quoted;
	char	*here_name;

	here_name = create_heredoc(shell, ".heredoc");
	fd = open(here_name, O_WRONLY | O_CREAT, 00644);
	if (fd == -1)
	{
		shell->status = 1;
		free(here_name);
		ft_error(shell, 0, 2, "HERE_DOC: ", get_errnum(OPEN_FILE));
		return (clean_node(&del), NULL);
	}
	is_quoted(del->use.content, &quoted);
	while (g_signal != SIGINT
		&& write_heredoc(shell, *(del->use.content), fd, quoted))
		continue ;
	signal(SIGQUIT, handle_sigquit);
	close(fd);
	free(del->use.content);
	del->use.fd = open(here_name, O_RDONLY);
	unlink(here_name);
	if (g_signal == SIGINT)
		return (free(del), free(here_name), close(fd), NULL);
	return (free(here_name), del);
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
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	line = readline("heredoc>> ");
	if (!line)
	{
		printf("%s (wanted '%.*s')\n", get_errnum(EOL_DEL),
			(int)del.size, del.start);
		return (0);
	}
	if (!heredoc_cmp(line, del.start, del.size) || g_signal == SIGINT)
		return (free(line), 0);
	if (!quoted)
		expand_and_write(shell, line, fd);
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

static void	expand_and_write(t_shell *shell, char *line, int fd)
{
	int		i;
	char	**line_arr;
	t_token	*line_t;

	i = 0;
	line_t = (t_token *) ft_calloc(1, sizeof(t_token));
	line_t->start = line;
	line_t->size = ft_strlen(line);
	line_arr = expand(shell, line_t, NULL);
	free(line_t);
	while (line_arr[i])
	{
		write(fd, line_arr[i], ft_strlen(line_arr[i]));
		if (line_arr[i + 1])
			write(fd, " ", 1);
		free(line_arr[i]);
		i++;
	}
	free(line_arr);
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
