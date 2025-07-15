/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcopy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjacquet <sjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:31:51 by kerberos          #+#    #+#             */
/*   Updated: 2025/05/10 21:24:40 by sjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

/**
 * @brief Closes two file descriptors and returns a status code.
 *
 * @param fd1 (int) : First file descriptor to close.
 * @param fd2 (int) : Second file descriptor to close.
 * @param ret (int) : Value to return after closing.
 *
 * @return (int) : The value of ret.
 */
static int	close_all(int fd1, int fd2, int ret)
{
	close(fd1);
	close(fd2);
	return (ret);
}

/**
 * @brief Copies the contents of one file to another.
 *
 * @param spath (const char *) : Path to the source file.
 * @param dpath (const char *) : Path to the destination file.
 *
 * @return (int) : 0 on success, -1 on failure (file or read/write error).
 */
int	ft_fcopy(const char *spath, const char *dpath)
{
	int		sfd;
	int		dfd;
	char	buf[1024];
	ssize_t	bytes;

	sfd = open(spath, O_RDONLY);
	if (sfd == -1)
		return (-1);
	dfd = open(dpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dfd == -1)
		return (close(sfd), -1);
	bytes = read(sfd, buf, sizeof(buf));
	while (bytes > 0)
	{
		if (ft_putstr_fd(buf, dfd) == -1)
			return (close_all(sfd, dfd, -1));
		bytes = read(sfd, buf, sizeof(buf));
	}
	if (bytes == -1)
		return (close_all(sfd, dfd, -1));
	return (close_all(sfd, dfd, 0));
}
